const acc = document.querySelectorAll('.h3');

acc.forEach((acc) =>
    acc.addEventListener('click', () => {
        if (acc.parentNode.classList.contains('selected')) {
            acc.parentNode.classList.toggle('selected');
        } else {
                acc.parentNode.classList.remove('selected')
            acc.parentNode.classList.add('selected');
        }
    })
);

const slides = document.getElementsByClassName("contactusoption");
        const prev = document.querySelector(".prev");
        const next = document.querySelector(".next");
        const indicator = document.querySelector(".indicator")
        let index = 0;

        prev.addEventListener("click", function () {
            prevSlide();
            slidingPrev();
            updateIndicator();
            resetTimer();
        })
        next.addEventListener("click", function () {
            nextSlide();
            updateIndicator();
            resetTimer();
        })
        function circleIndicator() {
            for (let i = 0; i < slides.length; i++) {
                const div = document.createElement("div");

                div.setAttribute("onclick", "indicateSlide(this)")
                div.id = i;
                if (i == 0) {
                    div.classList = "active";
                }
                indicator.appendChild(div);
            }
        }
        circleIndicator();

        function indicateSlide(element) {
            index = element.id;
            changeSlide();
            updateIndicator();
            resetTimer();
        }

        function updateIndicator() {
            for (let i = 0; i < indicator.children.length; i++) {
                indicator.children[i].classList.remove("active");
            }
            indicator.children[index].classList.add("active");
        }

        function slidingPrev() {
            for (let i = 0; i <slides.length; i++) {
                slides[i].classList.remove("prev_ani");
            }
            slides[index].classList.add("prev_ani");
        }

        function prevSlide() {
            if (index == 0) {
                index = slides.length - 1;
            }
            else {
                index--;
            }

            changeSlide();
        }
        function nextSlide() {
            if (index == slides.length - 1) {
                index = 0;
            }
            else {
                index++;
            }
            changeSlide();
        }
        function changeSlide() {
            for (let i = 0; i < slides.length; i++) {
                slides[i].classList.remove("active");
                slides[i].classList.remove("prev_ani");
            }
            slides[index].classList.add("active");
           
        }

        function resetTimer() {
            clearInterval(timer);
            timer = setInterval(autoplay, 4000);
        }

        function autoplay() {
            nextSlide();
            updateIndicator();
        }
        let timer = setInterval(autoplay, 4000);