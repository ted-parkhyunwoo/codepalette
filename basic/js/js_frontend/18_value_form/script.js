let username = document.getElementById('name');
let city = document.getElementById('city');
let btn = document.querySelector("#submit");

btn.addEventListener('click', function(e) {
    //! form 의 action 을 비워뒀기때문에, redirection(현재는 새로고침)을 막기위해 event.preventDeafault() 첨부. 
    e.preventDefault();
    let uName = username.value;
    let uCity = city.value;
    alert(`이름: ${uName}, 도시: ${uCity}`);
})
