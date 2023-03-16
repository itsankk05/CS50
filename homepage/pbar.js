function move(bar, prog) {
  var elem = document.getElementById(bar + "-bar");
  var width = 1;
  elem.style.width = width + "%";
  setTimeout(frame, 500);
  function frame() {
    elem.style.width = prog + "%";
    elem.style.transition = "width 0.5s ease-in-out";
  }
}
