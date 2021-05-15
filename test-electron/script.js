
function init() {
	open('graph.json');
}

function open(path){

	var s = new sigma({
		container : 'container',
	});
	s.refresh();
	sigma.parsers.json(
		path,
		s,
		function () {
			var i,
				nodes = s.graph.nodes();
			len = nodes.length;
			for(i=0;i<len;i++){
				nodes[i].x = Math.random();
				nodes[i].y = Math.random();
				nodes[i].size = s.graph.degree(nodes[i].id);
				nodes[i].color = (nodes[i].dept == 'it')?"rgb(255,104,102)":"rgb(145,204,102)";

			}
		}
	);
	s.refresh();
	s.startForceAtlas2();
};