var jsMouseEnabled = true;
var jsTouchEnabled = true;
var jsPointerEnabled = true;
var PointerOnly = true;
function ToggleJsEvent() {
	InitializeApp(PointerOnly);
	PointerOnly = !PointerOnly; 
}
function InitializeApp(pointerOnly) {
	var elem = document.getElementById("body");
	if (pointerOnly) {
		console.log("Adding PointerEvent listeners");
		["pointerdown", "pointermove", "pointerup"].forEach(function(e) {
			elem.addEventListener(e, PointerHandler);
		});
		return;
	}
	["pointerdown", "pointermove", "pointerup"].forEach(function(e) {
		elem.removeEventListener(e, PointerHandler);
	});
	console.log("Adding MouseEvent");
	["mousedown", "mousemove", "mouseup"].forEach(function(e) {
		elem.addEventListener(e, MouseHandler);
	});
	console.log("Adding Touch");
	["touchstart", "touchmove", "touchend"].forEach(function(e) {
		elem.addEventListener(e, TouchHandler);
	});
}

var mousePressed = false;
var TouchDown = false;

function PointerHandler(event) {
	event.preventDefault();

	if (event.type == "pointerdown") {
		mousePressed = true;
		return;
	}
	if (event.type == "pointerup") {
		mousePressed = false;
		return;
	}
	if (mousePressed) {
		console.log("pointer");
		LogTo('jsInputLog', "black", "Pointer Input: x: " + event.pageX + " y: " + event.pageY);
		if (event.getCoalescedEvents) {
			var points = event.getCoalescedEvents();
			for(let coalesced of points) {
				LogTo('jsInputLog', "grey", "Coalesced Pointer Input: x: " + coalesced.pageX + " y: " + coalesced.pageY);

			}			
		}
	}


}

function MouseHandler(event) {
	event.preventDefault();
	if (event.type == "mousedown") {
		mousePressed = true;
		return;
	}
	if (event.type == "mouseup") {
		mousePressed = false;
		return;
	}

	if (mousePressed) {
		console.log("mouse");
		LogTo('jsInputLog', "Blue", "Mouse Input: x: " + event.pageX + " y: " + event.pageY);
	}
}

function TouchHandler(event) {
	event.preventDefault();
	if (event.type == "touchstart") {
		TouchDown = true;
		return;
	}
	if (event.type == "touchend") {
		TouchDown = false;
		return;
	}
	if (TouchDown) {
		LogTo('jsInputLog', "Blue", "Touch Input: x: " + event.pageX + " y: " + event.pageY);
	}
}
