
let res = window.document.getElementById("res");
document.eve

res.onclick = () => {
    let test = window.confirm("true or false?");
    if (test) {
        res.textContent = "TRUE!";
    } else 
        res.textContent = "FALSE!";
}


