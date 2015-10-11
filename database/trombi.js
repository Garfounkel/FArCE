$(document).ready(function () {

    $("form#TrombiIndexForm").submit(function () {
        var submit = $('.submit .btn');
        submit.attr('disabled', 'disabled');

        $.ajax({
            type: 'POST',
            url: '/trombinoscope/trombinoscope/index',
            data: $("form#TrombiIndexForm").serialize(),
            success: function(data) {
                var html = $.parseHTML(data);
                html = $(html).find("#trombi-container").html();
                $("#trombi-container").html(html);
            },
            complete: function() {
                submit.removeAttr('disabled');
            }
        });

        return false;
    });
});
