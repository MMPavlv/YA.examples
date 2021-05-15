const electron = require('electron');
const {app, BrowserWindow} = electron;
const child_process = require('child_process');
const Menu = electron.Menu;
const {globalShortcut} = require('electron');
let mainWindow;

function createWindow() {
	// Create the browser window.
	mainWindow = new BrowserWindow({
		width: 800,
		height: 600,
		webPreferences: {
			nodeIntegration: true,
			devTools: true
		}
	});
	// and load the index.html of the app.
	mainWindow.loadFile('index.html');

	mainWindow.on('closed', function () {
		mainWindow = null
	})
}

app.on('ready', function () {
	createWindow();
	const {dialog} = require('electron');
	const template = [
		{
			label: 'File',
			submenu: [
				{
					label: 'Open',
					submenu: [
						{
							label: 'Open JSON',
							click() {
								//TODO errors

								let path = dialog.showOpenDialog({properties: ['openFile', 'multiSelections']})[0];
								if (path.length > 0) {
									mainWindow.webContents.send('ping', path);
								}
							}
						}
					]
				},
				{
					label: 'Save',
					submenu: [
						{
							label: 'Save As Ad.Matrix',
							click() {
								let path = dialog.showSaveDialog(null);
								if (path.length > 0) {
									mainWindow.webContents.send('save_file_ad', path);
								}
							}
						}
					]
				}
			]
		},
		{
			label: "Works"
		},
		{
			label: "Help"
		},
		{
			label: 'Exit',
			click() {
				app.quit();
			}
		}
	];
	const menu = Menu.buildFromTemplate(template);
	mainWindow.setMenu(menu);

	globalShortcut.register('CommandOrControl+Z', () => {
		mainWindow.webContents.send('ctrlz', "ctrlz");
		console.log('Ctrl+Z');
	});

	globalShortcut.register('CommandOrControl+X', () => {
		mainWindow.webContents.send('ctrlx', "ctrlx");
		console.log('Ctrl+X');
	})
});


app.on('window-all-closed', function () {
	if (process.platform !== 'darwin') {
		app.quit()
	}
});

app.on('activate', function () {
	if (mainWindow === null) {
		createWindow()
	}
});