function moduleDidLoad() {
  // var naclModule = document.getElementById('naclLogger');
  // naclModule.postMessage('hello');
}

function toggleDelay () {
  var naclModule = document.getElementById('naclLogger');
  naclModule.postMessage('ToggleDelay');
}

var color = "red";
function handleMessage(message) {
  console.log(message.data);
  if (message.data == "red") {
    color = "red";
  } else if (message.data == "blue") {
    color = "blue";
  } else {
     LogTo('naclInputLog', color, message.data);
  }

}
