const h1tag = document.querySelector("h1");
const addBtn = document.querySelector("#add");
const rmBtn = document.querySelector("#remove");
const tgBtn = document.querySelector("#toggle");
h1tag.textContent = "HELLO!";

addBtn.addEventListener("click", () => {
    h1tag.classList.add('text');
})

rmBtn.addEventListener("click", () => {
    h1tag.classList.remove('text');
})

tgBtn.addEventListener("click", () =>{
    h1tag.classList.toggle('text');
})
