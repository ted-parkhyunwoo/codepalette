let selection_sports = document.getElementById('user_sports');
let getSportBtn = document.querySelector('#pick_sports');

getSportBtn.addEventListener('click', () => {
    let isFootball = selection_sports.value === 'football';
    alert(isFootball? "축구를 선택하셨습니다!!": "...축구를 선택하지 않으셨습니다...");
})