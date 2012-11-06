<?php

    $file = "level.json";

    if(isset($_POST["newdata"])) {
        $json = jsonToData($_POST["newdata"]);
        file_put_contents($file, $json);
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

<?php

function jsonToData($json) {
    $data = "{";

    if(!is_object($json)) {
        $json = json_decode($json);
    }

    foreach($json as $k => $v) {
        $data .= "\"{$k}\" : ";

        if(is_object($v)) {
            $data .=  jsonToData($v);
        } else {
            $data .= "\"{$v}\"";
        }

        $data .= ",";
    }

    $data = rtrim($data, ",");

    return $data . "}";
}