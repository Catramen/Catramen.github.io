function LogTo(id, color, message) {
  var logEl = document.getElementById(id);
  var node = document.createElement("div");
  var font = document.createElement("font");
  font.color = color;
  font.textContent = message;
  node.appendChild(font);
  logEl.appendChild(node);
  logEl.scrollTop = logEl.scrollHeight;
};