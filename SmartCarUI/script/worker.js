// self.postMessage("okey");
let date = new Date();
let nDate;
var x = 100;
var count = 0;
while (true) {
  nDate = new Date();
  if (nDate - date > 1000) {
    x = x < 0.1 ? 0 : Math.round(x * 70) / 100;
    if (x > 0) self.postMessage(++count + " " + x);
    else count = 0;
    date = nDate;
  }
}
