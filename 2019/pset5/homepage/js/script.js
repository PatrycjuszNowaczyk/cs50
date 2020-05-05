// TODO
// convert jquery to vanilla js


// window.pageYOffset();
let sections = $('section').toArray();
let pageHeight = $(document).innerHeight();
let windowHeight = $(window).innerHeight();
window.addEventListener("scroll", () => {
    let windowOffset = $(window).scrollTop();
    console.log('window height: ' + windowHeight);
    console.log('page height: ' + pageHeight);
    console.log('window offset: ' + windowOffset);
    sections.forEach(element => {
        let elementYoffset = $(element).offset().top;
        console.log(elementYoffset);
        if (windowOffset + (windowHeight / 1.6) > elementYoffset) {
            $(element).addClass('show');
            $(element).find('.h1bg').addClass('h1bg--show');
            $(element).find('.heading').addClass('heading--yellow');
        }
        else {
            $(element).removeClass('show');
            $(element).find('.h1bg').removeClass('h1bg--show');
            $(element).find('.heading').removeClass('heading--yellow');
        }
        if (($(element).height() + elementYoffset) < (windowOffset + windowHeight / 4)) {
            $(element).removeClass('show');
            $(element).find('.h1bg').removeClass('h1bg--show');
            $(element).find('.heading').removeClass('heading--yellow');
        }
    });
    console.log(sections);


})

//         $('section').toggleClass("show", ($(window).scrollTop() > 1000));
//     });
// });
// $(document).ready(() => {
// $('section').hover(function () {
//     $(this).toggleClass('show');
//     $(this).find('.h1bg').toggleClass('h1bg--show');
//     $(this).find('.heading').toggleClass('heading--yellow');
// }),
//     () => {

//     }
// })

function closeMenu(event) {
    if (event.keyCode === 27) {
        let element = document.getElementsByClassName('navbar__burger')[0];
        element.classList.remove("open");
        element = document.getElementsByClassName('navbar__menu')[0];
        element.classList.remove("open");
    }
}

$('.navbar__toggler').click(function () {
    $('.navbar__burger').toggleClass('open');
    $('.navbar__menu').toggleClass('open');
    if ($('.navbar__menu').hasClass('open')) {
        document.addEventListener("keyup", closeMenu(event));
        $('.navbar__menu').click(() => {
            $('.navbar__burger').removeClass('open');
            $('.navbar__menu').removeClass('open');
        })
        document.removeEventListener("keyup", closeMenu(event));
    }
});

$('.container').find('.myRecentWorkBox').find('img').each(function () {
    let imgClass = (this.width / this.height > 1) ? 'wide' : 'tall';
    $(this).addClass(imgClass);
});


function setMyRecentWorkBoxHeight() {
    let MyRecentWorkBox = document.getElementsByClassName("myRecentWorkBox");
    let MyRecentWorkBoxWidth = MyRecentWorkBox[0].clientWidth;
    // console.log(MyRecentWorkBoxWidth);
    for (let i = 0; i < MyRecentWorkBox.length; i++) {
        MyRecentWorkBox[i].style.height = `${MyRecentWorkBoxWidth}px`;
    }
}


setMyRecentWorkBoxHeight();
window.addEventListener("resize", setMyRecentWorkBoxHeight);


//functions used in inline HTML

//autoresize contact textarea
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