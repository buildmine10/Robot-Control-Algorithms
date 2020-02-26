console.clear();

class Canvas {
	constructor(id, size, location){
		this.location = document.getElementById(location);
		this.location = document.createElement("div");
		this.location.id = `${location}`;
		document.body.append(this.location);
		
		this.canvas = document.createElement("canvas");
		this.ctx = this.canvas.getContext("2d");
		this.canvas.width = size;
		this.canvas.height = size;
		this.canvas.style.border = "2px solid deeppink";
		this.canvas.style.marginLeft = "2px";
		this.canvas.style.marginRight = "2px";
		
		this.size = size;
		
		document.getElementById(location).append(this.canvas);
		
		this.sprites = [];
		
		this.scale = 1;
		
		this.data = [];
		this.overlayData = [];
		for(let i = 0; i < size; i++){
			this.data.push([]);
			this.overlayData[i] = [];
			for(let j = 0; j < size; j++){
				this.data[i].push(0);
				this.overlayData[i][j] = undefined;
			}
		}
	}
	
	draw(){	
		var self = this;
		function toImage(){
			var image = self.ctx.createImageData(self.size * self.scale, self.size * self.scale);
			
			var scaledSize = self.size * self.scale;
			for(var x = 0; x < self.scale; x++){
				for(var y = 0; y < self.scale; y++){
				
					self.data.forEach((element, index1)=>{
						element.forEach((element, index2)=>{
							image.data[4 * (index1 * self.scale + x + ((scaledSize - self.scale) - index2 * self.scale + y) * self.size * self.scale) + 0] = element * 255;//red
							image.data[4 * (index1 * self.scale + x + ((scaledSize - self.scale) - index2 * self.scale + y) * self.size * self.scale) + 1] = element * 255;//gree
							image.data[4 * (index1 * self.scale + x + ((scaledSize - self.scale) - index2 * self.scale + y) * self.size * self.scale) + 2] = element * 255;//blue
							image.data[4 * (index1 * self.scale + x + ((scaledSize - self.scale) - index2 * self.scale + y) * self.size * self.scale) + 3] = 255;//alpha
						});
					});
					
				}
			}
			
			return image;
		}
		
		this.ctx.putImageData(toImage(), 0, 0);
	}//displays rendered data
	
	applySprite(sprite){
		if(sprite.x == undefined) sprite.x = 0;
		if(sprite.y == undefined) sprite.y = 0;
    
    var startX = (sprite.x < 0) ? 0 : sprite.x;
    var startY = (sprite.y < 0) ? 0 : sprite.y;
		
		for(let i = startX; i < sprite.x + sprite.data.length && i < this.size; i++){
		
			if(sprite.data[i - sprite.x] != undefined){
				for(let j = startY; j < sprite.y + sprite.data[i - sprite.x].length && j < this.size; j++){
					if(sprite.data[i - sprite.x][j - sprite.y] != undefined)
						if(sprite.isOverlay)
							this.overlayData[i][j] = sprite.data[i - sprite.x][j - sprite.y];
						else
							this.data[i][j] = sprite.data[i - sprite.x][j - sprite.y];
				}
			}

		}
	}//renders sprite data to the canvas
	
	addSprite(sprite){
		this.sprites.push(sprite);
	}//adds a sprite to the list of sprites to be rendered everytime renderSprites is called.
	
	renderSprites(){
		this.sprites.forEach(sprite=>{
			this.applySprite(sprite);
		});
	}//renders all linked sprites.
	
	subtract(array){
		var output = []
		for(let i = 0; i < this.size; i++){
			output[i] = [];
			for(let j = 0; j < this.size; j++){
				output[i][j] = this.data[i][j] - array[i][j];
			}
		}
		return output;
	}
	
	add(array){
		var output = []
		for(let i = 0; i < this.size; i++){
			output[i] = [];
			for(let j = 0; j < this.size; j++){
				output[i][j] = this.data[i][j] + array[i][j];
			}
		}
		return output;
	}
	
	multiply(array){
		var output = []
		for(let i = 0; i < this.size; i++){
			output[i] = [];
			for(let j = 0; j < this.size; j++){
				output[i][j] = this.data[i][j] * array[i][j];
			}
		}
		return output;
	}
	
	divide(array){
		var output = []
		for(let i = 0; i < this.size; i++){
			output[i] = [];
			for(let j = 0; j < this.size; j++){
				output[i][j] = this.data[i][j] / array[i][j];
			}
		}
		return output;
	}
	
	power(array){
		var output = []
		for(let i = 0; i < this.size; i++){
			output[i] = [];
			for(let j = 0; j < this.size; j++){
				output[i][j] = Math.pow(this.data[i][j], array[i][j]);
			}
		}
		return output;
	}
  
	clearAll(){
		this.clear();
		this.clearOverlay();
	}
	
  clear(){
  	this.data = [];
		for(let i = 0; i < this.size; i++){
			this.data[i] = [];
			for(let j = 0; j < this.size; j++){
				this.data[i][j] = 0;
			}
		}
  }
	
	clearOverlay(){
		this.overlayData = [];
		for(let i = 0; i < this.size; i++){
			this.overlayData[i] = [];
			for(let j = 0; j < this.size; j++){
				this.overlayData[i][j] = undefined;
			}
		}
	}
	
	getValueAt(x, y){
		if(x >= this.data.length || x < 0) return 0;
		if(y >= this.data.length || y < 0) return 0;
		return this.data[x][y];
	}
	
	resize(size){
		this.canvas.width = this.size * size;
		this.canvas.height = this.size * size;
		this.scale = size;
	}
	
	maximum(array, max) {
		array.forEach(element => {
			var value;
			if (element instanceof Array)
				value = this.maximum(element, max);
			else
				value = element;

			if (value > max || max == undefined)
				max = value;
		});
		return max;
	}

	minimum(array, min) {
		array.forEach(element => {
			var value;
			if (element instanceof Array)
				value = this.minimum(element, min);
			else
				value = element;

			if (value < min || min == undefined)
				min = value;
		});
		return min;
	}

	normalize() {
		var min = this.minimum(this.data);
		var max = this.maximum(this.data);
		
		function adjust(array) {
			var output = [];
			array.forEach(element => {
				if (element instanceof Array)
					output.push(adjust(element));
				else
					output.push((element - min) / (max - min));
			});
			return output;
		}

		this.data = adjust(this.data);
	}
}

class Sprite {
	constructor(size, isOverlay){
		this.data = [];
		
		if(isOverlay == undefined) isOverlay = false;
		this.isOverlay = isOverlay;
		
		for(let i = 0; i < size; i++){
			this.data[i] = [];
			for(let j = 0; j < size; j++){
				this.data[i][j] = undefined;
			}
		}
		
		this.size = size;
		this.x = 0;
		this.y = 0;
	}
	
	clear(){
		var size = this.size;
		for(let i = 0; i < size; i++){
			this.data[i] = [];
			for(let j = 0; j < size; j++){
				this.data[i][j] = undefined;
			}
		}
	}
	
	setData(data){
		this.data = data;
	}
	
	setArea(value, x, y, width, height){
  	if(x >= this.data.length){
      for(let i = this.data.length; i < x; i++){
    		this.data[i] = [];
    	}
    }

    
		for(let i = x; i < x + width; i++){
			if(this.data[i] == undefined) this.data[i] = [];
			for(let j = y; j < y + height; j++){
				this.data[i][j] = value;
			}
		}
	}
	
	addLine(value, startX, startY, endX, endY){
		var lowX = Math.min(startX, endX);
		var lowY = Math.min(startY, endY);
		var highX = Math.max(startX, endX);
		var highY = Math.max(startY, endY);

		var location = {x: startX, y: startY};
		var unitVector = {x: endX - startX, y: endY - startY};
		let mag = Math.sqrt(Math.pow(unitVector.x, 2) + Math.pow(unitVector.y, 2));
		unitVector.x /= mag;
		unitVector.y /= mag;
		
		var otherX = (startX == highX) ? lowX : highX;
		var otherY = (startY == highY) ? lowY : highY;
		
		var xPolarity = Math.sign(startX - otherX);
		var yPolarity = Math.sign(startY - otherY);
		
		while(Math.sign(location.x - otherX) == xPolarity && Math.sign(location.y - otherY) == yPolarity){
			var roundX = Math.round(location.x);
			var roundY = Math.round(location.y);
			
			if(!(roundX < 0 || roundX >= this.size || roundY < 0 || roundY >= this.size)){
				this.data[roundX][roundY] = value;			
			}
			
			location.x += unitVector.x;
			location.y += unitVector.y;
		}
		
		/*
		function isIntersecting(startX, startY, endX, endY, pointX, pointY){
			var numerator = startY * (pointX - endX) + endY * (startX - pointX) + pointY * (endX - startX);
			var denominator = (endX - startX);
			
			if(denominator == 0)
				return Math.abs(startX - pointX) <= 1;
			else 
				return Math.abs(numerator / denominator) <= 1;
		}

		if(startX != endX){
			for(let i = Math.min(startX, endX); i < Math.max(startX, endX); i++){
				if(this.data[i] == undefined) this.data[i] = [];
				for(let j = Math.min(startY, endY); j <= Math.max(startY, endY); j++){
					if(isIntersecting(startX, startY, endX, endY, i, j))
						this.data[i][j] = value;
						
				}
			}
		}else{
			if(this.data[startX] == undefined) this.data[startX] = [];
			for(let j = Math.min(startY, endY); j < Math.max(startY, endY); j++){
				if(isIntersecting(startX, startY, endX, endY, startX, j))
					this.data[startX][j] = value;
					
			}
		}
		*/
	}
	
	randomize(size){
		var output = [];
		for(let i = 0; i < size; i++){
			output[i] = [];
			for(let j = 0; j < size; j++){
				output[i][j] = Math.random();
			}
		}
		this.data = output;
	}
	
	rescale(inputScale){
		var scale = 1 / inputScale;
		function findLargest(largest, current){
			return (largest < current.length) ? current.length : largest;
		}
		var newLength = Math.floor(this.data.length / scale);
		var width = this.data.reduce(findLargest, 0);
		var newWidth = Math.floor(width / scale);
		
		var output = [];
		
		for(let i = 0; i < newLength; i++){
			output[i] = [];
			for(let j = 0; j < newWidth; j++){
				var total = 0;
				var counter = 0;
				var undefineds = 0;
				
				for(let n = 0; n < 1 / scale; n++){
					for(let m = 0; m < 1 / scale; m++){
						if(((i * scale) + n < this.data.length) && ((j * scale) + m < width)){//the if statement makes it safer
							if(this.data[(i * scale) + n] == undefined)  undefineds++;
							else if(this.data[(i * scale) + n][(j * scale) + m] == undefined) undefineds++;
							else{
								total += this.data[(i * scale) + n][(j * scale) + m];
								counter++;
							}
						}
					}
				}
				
				if(undefineds > Math.pow(1 / scale, 2)) 
					output[i][j] = undefined;
				else 
					output[i][j] = total / counter;
			}
		}
		this.data = output;
	}
	
	vertexShader(point){
			if(point.z > 0)
				return {x: (point.x + point.z) / (point.z * 2), y: (point.y + point.z) / (point.z * 2)};
			else
				return undefined;
		}
	
	add3DLine(value, start, end){
		var point1 = this.vertexShader(start);
		var point2 = this.vertexShader(end);
		
		this.addLine(value, Math.round(point1.x * this.size), Math.round(point1.y * this.size), Math.round(point2.x * this.size), Math.round(point2.y * this.size));
	}
  
  addTri(value, point1, point2, point3, antiAliasedSides){
		if(Array.isArray(point1)){
			antiAliasedSides = point2;
			point2 = point1[1];
			point3 = point1[2];
			point1 = point1[0];
		}
		
		if(antiAliasedSides == undefined)
			antiAliasedSides = [];
			
		function isIntersecting(point1, point2, point3, pointX, pointY){//corner 1 is bottom left, corner 2 is top right, other is the other point
			var xList = [point1.x, point2.x, point3.x];
			var yList = [point1.y, point2.y, point3.y];
			
			var corner1 = {x: 0, y: 0};
			var corner2 = {x: 0, y: 0};
			var otherPoint = {x: 0, y: 0};
			
			
			corner1.x = xList.splice(xList.indexOf(Math.min(point1.x, Math.min(point2.x, point3.x))), 1)[0];
			corner1.y = yList.splice(yList.indexOf(Math.min(point1.y, Math.min(point2.y, point3.y))), 1)[0];
			
			corner2.x = xList.splice(xList.indexOf(Math.max(point1.x, Math.max(point2.x, point3.x))), 1)[0];
			corner2.y = yList.splice(yList.indexOf(Math.max(point1.y, Math.max(point2.y, point3.y))), 1)[0];
			
			otherPoint.x = xList[0];
			otherPoint.y = yList[0];
			
			
			var isInSquare = (pointX >= corner1.x) && (pointX <= corner2.x) && (pointY >= corner1.y) && (pointY <= corner2.y);
			var areCornersVertical = corner1.x == corner2.x; 
			
			
			if(areCornersVertical){
				return isInSquare;//if on the same side
			}else{
				function slope(point1, point2){
					return (point1.y - point2.y) / (point1.x - point2.x);
				}
				
				function isAbove(toCheck, point1, point2){
					return toCheck.y > slope(point1, point2) * (toCheck.x - point1.x) + point1.y;
				}
				
				function distanceAbove(toCheck, point1, point2){
					return toCheck.y - (slope(point1, point2) * (toCheck.x - point1.x) + point1.y);
				}

				if((isAbove(point1, point2, point3) == isAbove({x: pointX, y: pointY}, point2, point3)) && (isAbove(point2, point1, point3) == isAbove({x: pointX, y: pointY}, point1, point3)) && (isAbove(point3, point2, point1) == isAbove({x: pointX, y: pointY}, point2, point1))){
					var distances = [1];
					if(antiAliasedSides.includes(0))
						distances.push(Math.abs(distanceAbove({x: pointX, y: pointY}, point2, point3)));
					if(antiAliasedSides.includes(1))
						distances.push(Math.abs(distanceAbove({x: pointX, y: pointY}, point1, point3)));
					if(antiAliasedSides.includes(2))
						distances.push(Math.abs(distanceAbove({x: pointX, y: pointY}, point2, point1)));
					var DistanceAbove = distances.sort((a, b)=>{return a - b;})[0];
					
					if(DistanceAbove > 1)
						DistanceAbove = 1;
					return DistanceAbove;
				}     
				else
					return false;
				
				
			}
			
		}
    
		function findColor(point1, point2, point3, maxValue, x, y){			
			var colors = [1, 1, 1];//point1 = 0, point2 = 1, point3 = 0.5
			
			var w1 = ((point2.y - point3.y) * (x - point3.x)  +  (point3.x - point2.x) * (y - point3.y))   /   ((point2.y - point3.y) * (point1.x - point3.x)  +  (point3.x - point2.x) * (point1.y - point3.y));
			var w2 = ((point3.y - point1.y) * (x - point3.x)  +  (point1.x - point3.x) * (y - point3.y))   /   ((point2.y - point3.y) * (point1.x - point3.x)  +  (point3.x - point2.x) * (point1.y - point3.y));
			var w3 = 1 - w1 - w2;

			var color = colors[0] * w1 + colors[1] * w2 + colors[2] * w3;
			return color * value;
		}
		
		if(point1.z > 0 || point2.z > 0 || point3.z > 0){
			var adjustedPoint1 = this.vertexShader(point1);
			var adjustedPoint2 = this.vertexShader(point2);
			var adjustedPoint3 = this.vertexShader(point3);

			adjustedPoint1.x *= this.size;
			adjustedPoint1.y *= this.size;
			adjustedPoint2.x *= this.size;
			adjustedPoint2.y *= this.size;
			adjustedPoint3.x *= this.size;
			adjustedPoint3.y *= this.size;

			for(let i = 0; i < this.size; i++){
				if(this.data[i] == undefined) this.data[i] = [];
				for(let j = 0; j < this.size; j++){
					var isIntersectingResults = isIntersecting(adjustedPoint1, adjustedPoint2, adjustedPoint3, i, j);
					//if(isIntersectingResults != false)
						//console.log(isIntersectingResults)
					if(isIntersectingResults != false)
						this.data[i][j] = findColor(adjustedPoint1, adjustedPoint2, adjustedPoint3, value, i, j) * isIntersectingResults;
				}
			}
		}
  }
	
	add3DPoint(point){
		//log.innerText = JSON.stringify(point);
		var point2D = this.vertexShader(point);
		log.innerText = JSON.stringify(point2D);
		if(point2D != undefined)
			this.setArea(1, Math.round(point2D.x * this.size), Math.round(point2D.y * this.size), 1, 1);
	}
	
	static rotateX(point, angle){
		return {x: point.x, y: Math.cos(angle) * point.y - Math.sin(angle) * point.z, z: Math.sin(angle) * point.y + Math.cos(angle) * point.z};
	}
	
	static rotateY(point, angle){
		return {x: Math.cos(angle) * point.x + Math.sin(angle) * point.z, y: point.y, z: -Math.sin(angle) * point.x + Math.cos(angle) * point.z};
	}
	
	static rotateZ(point, angle){
		return {x: Math.cos(angle) * point.x - Math.sin(angle) * point.y, y: Math.sin(angle) * point.x + Math.cos(angle) * point.y, z: point.z};
	}
	
	static positionPoints(points, cameraPosition, cameraRotation, pointOffset){
		var output = [];
		points.forEach(point=>{
			var worldSpace = {x: point.x + pointOffset.x, y: point.y + pointOffset.y, z: point.z + pointOffset.z};
			var cameraSpace =  {x: worldSpace.x - cameraPosition.x, y: worldSpace.y - cameraPosition.y, z: worldSpace.z - cameraPosition.z};
			var yRotation = this.rotateY(cameraSpace, cameraRotation.y);//{x: Math.cos(cameraRotation.y) * cameraSpace.x + Math.sin(cameraRotation.y) * cameraSpace.z, y: cameraSpace.y, z: -Math.sin(cameraRotation.y) * cameraSpace.x + Math.cos(cameraRotation.y) * cameraSpace.z};
			var zRotation = this.rotateZ(yRotation, cameraRotation.z);
			var xRotation = this.rotateX(zRotation, cameraRotation.x);
			output.push(xRotation);
		});
		return output;
	}
	
	maximum(array, max) {
		array.forEach(element => {
			var value;
			if (element instanceof Array)
				value = this.maximum(element, max);
			else
				value = element;

			if (value > max || max == undefined)
				max = value;
		});
		return max;
	}

	minimum(array, min) {
		array.forEach(element => {
			var value;
			if (element instanceof Array)
				value = this.minimum(element, min);
			else
				value = element;

			if (value < min || min == undefined)
				min = value;
		});
		return min;
	}

	normalize() {
		var min = this.minimum(this.data);
		var max = this.maximum(this.data);
		
		function adjust(array) {
			var output = [];
			array.forEach(element => {
				if (element instanceof Array)
					output.push(adjust(element));
				else
					output.push((element - min) / (max - min));
			});
			return output;
		}

		this.data = adjust(this.data);
	}
}

function readTextFile(file) {
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
                alert(allText);
            }
        }
    }
    rawFile.send(null);
}

readTextFile("InterfaceFile.txt")

var canvas = new Canvas(0, 100, 0);
var sprite = new Sprite(100);
canvas.resize(1);
canvas.addSprite(sprite);

var cameraPosition = {x: 0, y: 0, z: 0};
var rotation = {x: 0, y: 0, z: 0};


var points = [{x: 0, y: 0, z: 2}, {x: 1, y: 0, z: 2}, {x: 1, y: 2.5, z: 2}];

setInterval(()=>{
	var positionedPoints = Sprite.positionPoints(points, cameraPosition, rotation, {x: 0, y: -1, z: 0});				
	sprite.addTri(1, positionedPoints[0], positionedPoints[1], positionedPoints[2], [0]);

	canvas.renderSprites();
	canvas.draw();
})
