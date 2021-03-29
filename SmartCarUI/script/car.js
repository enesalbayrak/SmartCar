/*var wait = async (time) => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve();
    }, time);
  });
};

(async () => {
  let x = 0;
  while (true) {
    await wait(1000);
    console.log(++x);
  }
})();*/

let worker = new Worker("script/worker.js");
worker.addEventListener("message", function (e) {
  console.log(e.data);
});
