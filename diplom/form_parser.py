import sys
import numpy as np
import cv2
from matplotlib import pyplot as plt
import os
import math
import time

affine_coords = [[0, 0], [2273, 0], [0, 3240]] #Система координат, которой мы приводим реальные бланки
square_length = 500 #Ширина квадрата, который мы будем брать в углах реального бланка для поиска опорных точек
box_length = 60 #ширина квадратика для галочки
box_length_ = box_length+14
indent = 11 #количество пикселей, чтобы отступать от границы вглубь квадратика
templates = ['template_sex1', 'template_age1', 'template_education1', 'template_job1', 'template_occupation1',
			 'template_uni1', 'template_status1', 'template_answers1'] #переменные для загрузки отдельных шаблонов
path = os.path.dirname(os.path.abspath(__file__)) + '\\' #переменная с путем к папке с файлом
temps = {} #глобальная переменная для хранения изображений шаблонов блоков
blocks = {}

def getRawData(filename, tmps): #функция анализирующая отдельное изображение по пути файла
	tst = filename.split('.')
	if(tst[len(tst)-1] != "jpg" and tst[len(tst)-1] != "jpeg" and tst[len(tst)-1] != "png"):
		print("Wrong file type. Should be .jpg or .png")
		return ""

	global temps
	temps = tmps
	affine = getAffinImage(filename)
	result = findValues(affine)
	return result

def getAffinImage(filename): #функция, возвращающая основную часть бланка после аффинных преобразований
	im = cv2.imread(filename)
	coords = findCircles(im)
	roi = Affine(im, coords)
	return roi

def findCircles(image): #основная функция поиска кругов
	quarters = getQuarters(image) #получаем квадраты
	height, width, channels = image.shape
	it = 0
	coords = []
	for quarter in quarters:
		coord = findCirclesContour(quarter) #находим координаты кругов с помощью контуров
		if(coord == None): #если не нашлись
			coord = findCirclesTemplate(quarter) #ищем с помощью matchTemplate
		#дальше полученные координаты приводим к координатам реального бланка

		if (it == 0):
			coord_ = coord
			pass
		elif (it == 1):
			coord = [(coord[0][0] + width - square_length, coord[0][1]),
					 (coord[1][0] + width - square_length, coord[1][1])]
		elif (it == 2):
			coord = [(coord[0][0], coord[0][1] + height - square_length),
					 (coord[1][0], coord[1][1] + height - square_length)]
		elif (it == 3):
			coord = [(coord[0][0] + width - square_length, coord[0][1] + height - square_length),
					 (coord[1][0] + width - square_length, coord[1][1] + height - square_length)]

		center = [(coord[0][0] + coord[1][0]) // 2, (coord[0][1] + coord[1][1]) // 2]
		coords.append(center)
		it += 1
	return coords

def getQuarters(image): #функция, возвращающая 4 изображения с угловыми квадратами бланка
	height, width, channels = image.shape
	im1 = image[0:square_length, 0:square_length]
	im2 = image[0:square_length, width - square_length:width]
	im3 = image[height - square_length:height, 0:square_length]
	im4 = image[height - square_length:height, width - square_length:width]
	return [im1, im2, im3, im4]

def findCirclesContour(image_color): #функция, находящая координаты опорных кругов для аффинных преобразований по контуру
	image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY) #делаем серое изображение
	image_gray = cv2.medianBlur(image_gray, 5) #убираем шумы

	ret,thresh1 = cv2.threshold(image_gray,200,255,cv2.THRESH_BINARY) #производим бинаризацию на черное и белое(от 0 до 200 — черное)
	circles = cv2.HoughCircles(thresh1, cv2.HOUGH_GRADIENT, 1, 40, param1=20, param2=10, minRadius=10, maxRadius=50) #находим круги с заданными параметрами
	if circles is not None:
		circles = np.uint16(np.around(circles)) #Приводим к специальному формату
		for i in circles[0, :]:
			center = (i[0], i[1])
			radius = i[2]
			rad = radius - 8
			roi = thresh1[maxZero(int(center[1])-rad):center[1]+rad,maxZero(int(center[0])-rad):center[0]+rad] #вырезаем область внутри круга

			if(checkColor(roi)<20): #проверяем на ее среднее значение пикселей, если меньше определенного значения то это практически гарантированно нужным нам круг
				return [(maxZero(int(center[0])-radius), maxZero(int(center[1])-radius)), (center[0]+radius, center[1]+radius)] #возвращаем координаты круга

def maxZero(nm): #внутренняя функция для обработки случайных отрицательных координат
	if(nm <= 0):
		return 0
	else:
		return nm

def checkColor(image): #функция возвращает среднее значение пикселей изображения
	return image.mean(axis=0).mean(axis=0).sum() #.mean возвращает n-1 массив средних значений массива размерности n, упорядоченный по нулевому измерения

def findCirclesTemplate(image_color): #функция нахождения кругов с помощью matchTemplate
	template = cv2.imread('template_circle.png', 0) #загрузка изображения круга
	w, h = template.shape[::-1]
	image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
	res = cv2.matchTemplate(image_gray, template, cv2.TM_CCORR_NORMED)
	min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
	top_left = max_loc
	bottom_right = (top_left[0] + w, top_left[1] + h)
	return [top_left, bottom_right] #возвращение координат области, в которой заключен круг


def Affine(im, coords): #производятся аффинные преобразования
	srcTri = np.array([coords[0], coords[1], coords[2]]).astype(np.float32)
	dstTri = np.array(affine_coords).astype(np.float32)
	warp_mat = cv2.getAffineTransform(srcTri, dstTri)
	warp_dst = cv2.warpAffine(im, warp_mat, (2270, 3300))
	roi = warp_dst[0:affine_coords[2][1], 0:affine_coords[1][0]] #получаем область внутри реального бланка, которая нужным образом отмашстабирована и повернута
	return roi

def findValues(image_color): #функция, которая находит значения всех маленьких квадратиков в каждом шаблоне.
	#Работает частично из-за причин описанных выше(нет функции анализатора отдельной зоны с квадратом)
	image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
	darkness = {} #словарь в котором хранятся массивы значений затемненности квадратиков в удобной для анализа форме
	for template in templates: #идем по шаблону
		darkness[template] = []
		deep_color_copy = np.copy(image_color) #копируем бланк(уже после аффинных преобразований)
		coords = getArea(deep_color_copy, template) #получаем координаты шаблона
		crop_color = deep_color_copy[coords[0][1]:coords[1][1], coords[0][0]:coords[1][0]] #обрезаем его
		crop_gray = cv2.cvtColor(crop_color, cv2.COLOR_BGR2GRAY)
		#Для каждого шаблона вызываем соответствуюущую функцию-анализатор и кладем полученные значения в словарь
		global blocks
		blocks[template] = crop_color
	return getInfo()

def getArea(image_color, temp): #функция, возвращающая координаты на бланке, внутри которых находится нужный нам шаблон, с помощью matchTemplate
	template = temps[temp]
	w, h = template.shape[::-1]
	image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
	res = cv2.matchTemplate(image_gray, template, cv2.TM_CCORR_NORMED)
	min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
	top_left = max_loc
	bottom_right = (top_left[0] + w, top_left[1] + h)
	return [top_left, bottom_right]

#дальше идет несколько функций для каждого шаблона, которые по заданным координатам ищут зоны с потенциальным нахождением квадратов
#работают по одинаковому принципу: берется координата одного квадрата и от нее на равных интервалах берутся другие квадраты
#Но каждый случай индивидуален из-за разных координат и внутреннего устройства
#Пока функции возвращают нули, так как нет функции, которая бы анализировала зоны с квадратами, находила контуры квадратов и вырезала их внутреннюю часть
#Отступы нужны, чтобы захватывать область, в которой находится квадрат

def Cycle(image_color, outer_indent_x, outer_indent_y, shift_x = 0, shift_y = 0, its = 0):
	res = []
	for i in range(its):
		roi = Crop(image_color,outer_indent_x,outer_indent_y)
		outer_indent_x += shift_x
		outer_indent_y += shift_y
		res.append(analyzeSquare(roi, '_'))
	return res

def Crop(image_color,outer_indent_x,outer_indent_y):
	return image_color[outer_indent_y:outer_indent_y+box_length_, outer_indent_x:outer_indent_x+box_length_]

def getInfo():
	result = {}

	#sex
	image_color = blocks['template_sex1']
	result['template_sex1'] = Cycle(image_color, 13, 53, 0, box_length_, 2)

	#age
	image_color = blocks['template_age1']
	result['template_age1'] = Cycle(image_color, 160, 53, 0, 78, 9) + Cycle(image_color, 13, 105, 0, 78, 10)

	#education
	image_color = blocks['template_education1']
	outer_indent_x = 13
	outer_indent_y = 106

	res = []
	for i in range(5):
		roi = Crop(image_color, outer_indent_x, outer_indent_y)
		if(i!=3):
			outer_indent_y += 233 #смещение к следующему квадратику
		else:
			outer_indent_y += 208 #смещение к следующему квадратику
		res.append(analyzeSquare(roi, 'education'))
	result['template_education1'] = res

	#job
	image_color = blocks['template_job1']
	result['template_job1'] = Cycle(image_color, 13, 106, 0, 130, 8)

	#occupation
	image_color = blocks['template_occupation1']
	result['template_occupation1'] = Cycle(image_color, 13, 132, 0, 130, 2) + Cycle(image_color, 13, 800, 0, 130, 3)

	#uni
	image_color = blocks['template_uni1']
	result['template_uni1'] = Cycle(image_color, 13, 80, 0, 78, 3)

	#status
	image_color = blocks['template_status1']
	st1 = Crop(image_color, 13, 80)
	st2 = Crop(image_color, 13, 208)
	st3 = Crop(image_color, 693, 80)
	st4 = Crop(image_color, 693, 208)
	st5 = Crop(image_color, 1493, 80)
	st6 = Crop(image_color, 1230, 208)
	st7 = Crop(image_color, 1860, 208)
	result['template_status1'] = [analyzeSquare(st1, '_'), analyzeSquare(st2, '_'), analyzeSquare(st3, '_'), analyzeSquare(st4, '_'),
		analyzeSquare(st5, '_'), analyzeSquare(st6, '_'), analyzeSquare(st7, '_')]

	#answers
	image_color = blocks['template_answers1']
	outer_indent_x1 = 276
	outer_indent_y1 = 104
	res1 = []
	for i in range(10):
		outer_indent_x1 = 276
		res1 += Cycle(image_color, outer_indent_x1, outer_indent_y1, 122, 0, 6)
		outer_indent_y1 += 78

	res2 = []
	outer_indent_y1 = 104
	for i in range(10):
		outer_indent_x1 = 1277
		res2 += Cycle(image_color, outer_indent_x1, outer_indent_y1, 122, 0, 6)
		outer_indent_y1 += 78

	new_roi = image_color[90:850,1000:1130]
	result['template_answers1'] = (res1+res2, new_roi.mean(axis=0).mean(axis=0).sum()/3)
	return result

#Определение затемненности квадрата
def analyzeSquare(image_color, template):
	image_gray = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
	ret,image_binary = cv2.threshold(image_gray,200,255,cv2.THRESH_BINARY)
	np_arr_ver = image_binary.mean(axis=1)
	np_arr_hor = image_binary.mean(axis=0)
	rs = getCheckBox(np_arr_ver, np_arr_hor)#нахождение границ квадрата

	rs2 = (rs[0][0], rs[0][1])
	rs3 = (rs[1][0], rs[1][1])

	rs0 = (rs[0][0]+indent, rs[0][1]+indent)
	rs1 = (rs[1][0]-indent, rs[1][1]-indent)

	if(rs[0] == (-1,-1)):
		return -1

	new_roi = image_color[rs0[1]:rs1[1],rs0[0]:rs1[0]]#вырезание области внутри квадрата, чтобы не задеть границу
	res = new_roi.mean(axis=0).mean(axis=0).sum()/3#вычисление затемненности квадрата

	return res

#функция нахождения границ квадрата
#принимает в себя средние значения пикселей по вертикали и по горизонтали
#Находятся два крайних значения контура квадрата, а потом объединяются
def getCheckBox(np_arr_ver, np_arr_hor):
	rs1 = getCheckBoxS(np_arr_ver, np_arr_hor)
	rs2 = getCheckBoxB(np_arr_ver, np_arr_hor)
	return [rs1[0], rs2[0]]

#функция нахождения границ квадрата слева-направо, сверху-вниз
#принимает в себя средние значения пикселей по вертикали и по горизонтали
#алгоритм обходит изображение, перемещая по нему 4 точки, образующие квадрат. Если показатель затемненности для каждой из таких точек по вертикали и горизонтали окажется подходящим
#то алгоритм решит, что квадрат найден
def getCheckBoxS(np_arr_ver, np_arr_hor):
	len_ver = len(np_arr_ver)
	len_hor = len(np_arr_hor)
	box_length_ = box_length-10
	for i in range(len_ver-box_length_):
		for j in range(len_hor-box_length_):
			if(np_arr_ver[i] < 70 and np_arr_ver[i+box_length_] < 70 and np_arr_hor[j] < 70 and np_arr_hor[j+box_length_] < 70):
				return [(j, i), (j+box_length_, i+box_length_)]
	return [(-1,-1),(-1,-1)]

#функция нахождения границ квадрата справа-налево, снизу-вверх
#принимает в себя средние значения пикселей по вертикали и по горизонтали
#алгоритм обходит изображение, перемещая по нему 4 точки, образующие квадрат. Если показатель затемненности для каждой из таких точек по вертикали и горизонтали окажется подходящим
#то алгоритм решит, что квадрат найден
def getCheckBoxB(np_arr_ver, np_arr_hor):
	len_ver = len(np_arr_ver)
	len_hor = len(np_arr_hor)
	box_length_ = box_length-10
	for i in range(len_ver-1, len_ver-box_length_-1, -1):
		for j in range(len_hor-1, len_hor-box_length_-1, -1):
			if(np_arr_ver[i] < 70 and np_arr_ver[i-box_length_] < 70 and np_arr_hor[j] < 70 and np_arr_hor[j-box_length_] < 70):
				return [(j, i), (j-box_length_, i-box_length_)]
	return [(-1,-1),(-1,-1)]

def getMin(arr):
	return arr.index(min(arr))

def getMean(arr):
	return sum(arr)/len(arr)

def getSigma(arr):
	mean = getMean(arr)
	return math.sqrt(sum([(x - mean)**2 for x in arr])/(len(arr) - 1))

#Функция для анализа бланка
#принимает в себя словарь со значениями затемненности для всех квадратиков бланка
#-1 — квадрат не распознано
#_ — не определено одно из чисел возраста
#[] — не определен ответ
#числа — номера ответов
def new_analyze(raw_data):
	final_result = {} #словарь, в который будут класться ответы
	for key in templates: #циклический обход всех блоков бланка
	#key — имя блока
	#raw_data[key] — массив показателей затемненности данного блока
		if (key == 'template_sex1'):
			if(-1 in raw_data[key]): #проверка на наличие данных о квадратиках
				final_result['sex'] = -1
				continue
			if (len(raw_data[key]) != 2): #проверка на количество квадратиков
				final_result['sex'] = -1
			else:
				if (raw_data[key][0] < raw_data[key][1]): #сравнение в лоб, какой квадрат затемненнее
					final_result['sex'] = '0'
				else:
					final_result['sex'] = '1'
		elif (key == 'template_age1'):
			if(-1 in raw_data[key]): #проверка на наличие данных о квадратиках
				final_result['age'] = -1
				continue
			final_result['age'] = -1
			if (len(raw_data[key]) == 19): #проверка на количество квадратиков
				final_result['age'] = ''
				#ниже идет разбиение показателей затемненности на два подблока
				_data1 = raw_data[key][0:9]
				_data2 = raw_data[key][9:19]
				num1 = getMin(_data1)
				num2 = getMin(_data2)
				#считаются два среднеквадратичных для показателей затемненности подблоков
				sigma1 = getSigma(_data1)
				sigma2 = getSigma(_data2)

				if(sigma1>4.5):#проверка на среднеквадратичное. Если проходит проверку, то выбирается квадратик с максимальной затемненностью.
					final_result['age'] += str(num1+1)
				else:
					final_result['age'] += '_'

				if(sigma2>4.5):
					final_result['age'] += str(num2)
				else:
					final_result['age'] += '_'
		elif (key == 'template_education1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				final_result['education'] = -1
				continue
			if (len(raw_data[key]) != 5): #проверка на количество квадратиков
				final_result['education'] = -1
			else:
				sigma = getSigma(raw_data[key]) #считается среднеквадратичное для показателей затемненности

				if(sigma>4.5):
					a=[0 for x in range(len(raw_data[key]))]
					a[raw_data[key].index(min(raw_data[key]))] = 1
					final_result['education'] = a
				else:
					final_result['education'] = []
		elif (key == 'template_job1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				final_result['job'] = -1
				continue

			if (len(raw_data[key]) != 8):#проверка на количество квадратиков
				final_result['job'] = -1
			else:
				sigma = getSigma(raw_data[key]) #считается среднеквадратичное для показателей затемненности
				if(sigma>4.5):
					a=[0 for x in range(len(raw_data[key]))]
					a[raw_data[key].index(min(raw_data[key]))] = 1
					final_result['job'] = a
				else:
					final_result['job'] = []
		elif (key == 'template_occupation1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				final_result['occupation'] = -1
				continue
			if (len(raw_data[key]) != 5):#проверка на количество квадратиков
				final_result['occupation'] = [-1 for x in range(8)]
			else:
				final_result['occupation'] = [0 for x in range(8)]
				sigma = getSigma(raw_data[key])#считается среднеквадратичное для показателей затемненности
				if(sigma>4.5):
					idx = raw_data[key].index(min(raw_data[key]))
					if(idx > 1)
						final_result['occupation'][idx] = 1
					else
						final_result['occupation'][idx+3] = 1
				else:
					final_result['occupation'] = []
		elif (key == 'template_uni1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				break

			if(not isinstance(final_result['occupation'], list)):
				continue

			if (len(raw_data[key]) == 3 and final_result['occupation'][1] == 1): #проверка на количество квадратиков и зависимость от выбора в блоке occupation
				sigma = getSigma(raw_data[key]) #считается среднеквадратичное для показателей затемненности

				if (sigma > 4.5):
					idx = raw_data[key].index(min(raw_data[key]))
					final_result['occupation'][idx+2] = 1
				else:
					final_result['occupation'][2:5] = [[],[],[]]
			elif(len(raw_data[key]) != 3):
				final_result['occupation'][2:5] = [-1,-1,-1]
		elif (key == 'template_status1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				final_result['status'] = -1
				continue
			if (len(raw_data[key]) != 7): #проверка на количество квадратиков
				final_result['status'] = -1
			else:
				sigma = getSigma(raw_data[key]) #считается среднеквадратичное для показателей затемненности
				if(sigma>4.5):
					a=[0 for x in range(len(raw_data[key]))]
					a[raw_data[key].index(min(raw_data[key]))] = 1
					final_result['status'] = a
				else:
					final_result['status'] = []
		elif (key == 'template_answers1'):
			if(-1 in raw_data[key]):#проверка на наличие данных о квадратиках
				final_result['answers'] = -1
				continue
			final_result['answers'] = []
			if (len(raw_data[key]) == 120): #проверка на количество квадратиков
				it = 0
				white = raw_data['white'] #показатель затемненности фона
				for i in range(0,120,6): #последовательный обход строк в блоке ответов
					ag = raw_data[key][i,i+6]
					ag = [white - x for x in ag]
					b = []
					min_ = min(ag)
					max_ = max(ag)
					for j in range(6):
						if(a[j]*3<max_):#отсечение всех квадратиков, чья затемненность более чем в три раза меньше максимальной
							final_result['answers'].append(0)
							b.append(0)
						else:
							final_result['answers'].append(1)
							b.append(1)
			else:
				final_result['answers'] = -1
	return final_result

def showImage(image): #функция для отображения изображений формата opencv
	#return ""
	plt.axis("off")
	plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
	plt.show()
