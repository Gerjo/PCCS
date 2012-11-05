<?php

    $file = "level.json";

    if(isset($_POST["newdata"])) {
        file_put_contents($file, $_POST["newdata"]);
        return;
    }

?>


<html>

    <?php
        foreach(glob("js/*.js") as $src) {
            print '<script src="' . $src . '"></script>';
        }
    ?>
    <script>
        $(document).ready(function () {
            var editor = new Editor();

            editor.load(<?php echo file_get_contents($file) ?>);

        });
    </script>
    <link rel="stylesheet" href="http://code.jquery.com/ui/1.9.1/themes/base/jquery-ui.css" />
    <script src="http://code.jquery.com/ui/1.9.1/jquery-ui.js"></script>
    <style>
        body, html {
            margin: 0px; background-color: grey;
        }
        div.gameobject {
            border-radius: 10px; padding: 1px;
            position: absolute; background-position: center center;
            background-repeat: no-repeat;
        }
    </style>
    <body>

    </body>

</html>