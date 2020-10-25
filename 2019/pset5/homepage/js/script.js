// TODO
// convert jquery to vanilla js


//console tests

const human = {
    name: `Tom`,
    surname: `Hedgehog`,
    introduce() {
        this.name = !!this.name ? this.name : '';
        this.surname = !!this.surname ? this.surname : '';
        console.log(`My name is ${this.name} ${this.surname}`);
    }
};

human.introduce();

const andrew = {
    name: `Andrew`
};

human.introduce.call(andrew);
//console tests end




// section show and hide effect
let sections = document.querySelectorAll("section");
let pageHeight = $(document).innerHeight();
let windowHeight = $(window).innerHeight();
$('section:first').addClass('show');
$('section:first').find('.h1bg').addClass('h1bg--show');
$('section:first').find('.heading').addClass('heading--yellow');
window.addEventListener("scroll", () => {
    let windowOffset = $(window).scrollTop();
    // console.log('window height: ' + windowHeight);
    // console.log('page height: ' + pageHeight);
    // console.log('window offset: ' + windowOffset);
    sections.forEach(element => {
        let elementYoffset = $(element).offset().top;
        // console.log(elementYoffset);
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
})
//-------------------------------------------------------------------------------------------


// close burger menu
function closeMenu(event) {
    if (event.keyCode === 27) {
        let element = document.getElementsByClassName('navbar__burger')[0];
        element.classList.remove("open");
        element = document.getElementsByClassName('navbar__menu')[0];
        element.classList.remove("open");
    }
}




let burger = document.querySelector('.navbar__toggler');
// let container = document.getElementById('container');

function clickCloseMenu() {
    document.querySelector('.navbar__burger').classList.remove('open');
    document.querySelector('.navbar__menu').classList.remove('open');
}

function toggleMenu() {
    if (document.querySelector('.navbar__burger').classList.contains('open')) {
        document.querySelector('.navbar__burger').classList.remove('open');
        document.querySelector('.navbar__menu').classList.remove('open');
        document.querySelector('.navbar__menu').removeEventListener('click', clickCloseMenu)
    }
    else {
        document.querySelector('.navbar__burger').classList.add('open');
        document.querySelector('.navbar__menu').classList.add('open');
        document.querySelector('.navbar__menu').addEventListener('click', clickCloseMenu)
    }
};

burger.addEventListener('click', toggleMenu);


// #6a9955
// $('.navbar__toggler').click(function () {
//     $('.navbar__burger').toggleClass('open');
//     $('.navbar__menu').toggleClass('open');
//     if ($('.navbar__menu').hasClass('open')) {
//         document.addEventListener("keyup", closeMenu(event));
//         $('.navbar__menu').click(() => {
//             $('.navbar__burger').removeClass('open');
//             $('.navbar__menu').removeClass('open');
//         })
//         document.removeEventListener("keyup", closeMenu(event));
//     }
// });

//-------------------------------------------------------------------------------------------


// check and add equal class to image in my recent work section
$('.container').find('.myRecentWorkBox').find('img').each(function () {
    let imgClass = (this.width / this.height > 1) ? 'wide' : 'tall';
    $(this).addClass(imgClass);
});
//-------------------------------------------------------------------------------------------


// set needed height at my recent work image containing divs
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
//-------------------------------------------------------------------------------------------



// contact validation

let contactMeForm = document.getElementById('contactMe');
let contactMeFormShowed = false;
let contactMeName = document.getElementById('contactMeName');
let contactMeMail = document.getElementById('contactMeMail');
let contactMeMessage = document.getElementById('contactMeMessage');
let contactMeSubmit = document.getElementById('contactMeSubmit');
let regExName = /^[a-z][a-z0-9 _.',\-]{1,29}$/i;
let regExMail = /^[a-z,A-Z,0-9,-,_,.]+@[a-z,A-Z.]+\.[a-z,A-Z]{2,3}$/i;
let validation = { name: false, mail: false, message: false };

window.addEventListener('scroll', function formValidationInit() {
    if (contactMeForm.classList.contains('show') && contactMeFormShowed === false) {
        console.log(contactMeForm);
        contactMeFormShowed = true;
        contactMeName.addEventListener('input', function validName() {
            if (regExName.test(contactMeName.value)) {
                console.log('name is valid')
                validation.name = true;
                // document.getElementsByClassName('contactMeNameBG')[0].style.background = "#0f0";
                // contactMeName.style.cssText = "box-shadow: 0 0 0 15px #0f0";
                contactMeName.classList.remove('bad');
                contactMeName.classList.add('good');
            }
            else {
                validation.name = false;
                console.log('name is invalid');
                // document.getElementsByClassName('contactMeNameBG')[0].style.background = "#f00";
                // contactMeName.style.cssText = "box-shadow: 0 0 0 15px #f00";
                contactMeName.classList.remove('good');
                contactMeName.classList.add('bad');
            }
        });
        contactMeMail.addEventListener('input', function validMail() {
            if (regExMail.test(contactMeMail.value)) {
                validation.mail = true;
                contactMeMail.classList.remove('bad');
                contactMeMail.classList.add('good');
                console.log('mail is valid');
            }
            else {
                validation.mail = false;
                contactMeMail.classList.remove('good');
                contactMeMail.classList.add('bad');
                console.log('mail is invalid');
            }
        });
        contactMeMessage.addEventListener('input', function validMessage() {
            if (contactMeMessage.value.length > 1 && contactMeMessage.value.length < 1001) {
                contactMeMessage.classList.remove('bad');
                contactMeMessage.classList.add('good');
                validation.message = true;
                console.log('message is valid')
            }
            else {
                contactMeMessage.classList.remove('good');
                contactMeMessage.classList.add('bad');
                validation.message = false;
                console.log('message is invalid');
            }
        });
        window.removeEventListener('scroll', formValidationInit);
    }
    // console.log(contact.querySelector('section').;
});


function validSubmit(event) {
    for (const x in validation) {
        if (validation.hasOwnProperty(x)) {
            if (validation[x] === false) {
                event.preventDefault();
                console.log(`${x} FORM INVALID!!!`);
                switch (x) {
                    case 'name':
                        contactMeName.classList.remove('good');
                        contactMeName.classList.add('bad');
                        break;
                    case 'mail':
                        contactMeMail.classList.remove('good');
                        contactMeMail.classList.add('bad');
                        break;
                    case 'message':
                        contactMeMessage.classList.remove('good');
                        contactMeMessage.classList.add('bad');
                        break;
                    default:
                        console.log('there is something wrong with submit form validation');
                }

            }
            else {
                console.log(`${x} FORM VALID...`);
                switch (x) {
                    case 'name':
                        contactMeName.classList.remove('bad');
                        contactMeName.classList.add('good');
                        break;
                    case 'mail':
                        contactMeMail.classList.remove('bad');
                        contactMeMail.classList.add('good');
                        break;
                    case 'message':
                        contactMeMessage.classList.remove('bad');
                        contactMeMessage.classList.add('good');
                        break;
                    default:
                        console.log('there is something wrong with submit form validation');
                }
            }
        }
    }
}


//-------------------------------------------------------------------------------------------


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