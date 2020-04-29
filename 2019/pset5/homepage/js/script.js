
$('.navbar-toggler').click(function () {
    $('.burger').toggleClass('open');
});

$('.container').find('.myRecentWorkBox').find('img').each(function () {
    let imgClass = (this.width / this.height > 1) ? 'wide' : 'tall';
    $(this).addClass(imgClass);
});



function setMyRecentWorkBoxHeight() {
    let MyRecentWorkBox = document.getElementsByClassName("myRecentWorkBox");
    let MyRecentWorkBoxWidth = MyRecentWorkBox[0].clientWidth;
    console.log(MyRecentWorkBoxWidth);
    // let tempVar = document.getElementsByClassName('myRecentWorkBox');
    for (let i = 0; i < MyRecentWorkBox.length; i++) {
        MyRecentWorkBox[i].style.height = `${MyRecentWorkBoxWidth}px`;
    }
    // tempVar.style.height = MyRecentWorkBoxWidth;

}

setMyRecentWorkBoxHeight();
window.addEventListener("resize", setMyRecentWorkBoxHeight);

function addAutoResize() {
    document.querySelectorAll('[data-autoresize]').forEach(function (element) {
        element.style.boxSizing = 'border-box';
        var offset = element.offsetHeight - element.clientHeight;
        document.addEventListener('input', function (event) {
            event.target.style.height = 'auto';
            event.target.style.height = event.target.scrollHeight + offset + 'px';
        });
        element.removeAttribute('data-autoresize');
    });
}

