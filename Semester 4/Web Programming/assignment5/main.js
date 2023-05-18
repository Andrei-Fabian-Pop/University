$(function () {
    const slider = $("#slider");
    let images = slider.children("img");
    let speed = 5;
    let animate = true;

    function animateSlider() {
        slider.css('left', '+=' + speed);
        const firstImage = images.eq(0);
        const firstImageWidth = firstImage.outerWidth(true);
        if (parseFloat(slider.css('left')) >= firstImageWidth) {
            slider.prepend(images.last());
            slider.css('left', 0);
            images = slider.children('img');
        }
        if (animate) {
            window.requestAnimationFrame(animateSlider);
        }
    }

    images.on("click", function () {
        animate = false;
        const src = $(this).attr("src");
        $("#overlay img").attr("src", src);
        $("#overlay").fadeIn();
    });

    $("#overlay").on("click", function () {
        $(this).fadeOut();
        animate = true;
        animateSlider();
    });

    animateSlider();
});
