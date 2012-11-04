
function GameObject(json) {
    this._$node       = null;
    this._info        = json;
    this._isMouseDown = false;
    this.loadNode();

}

GameObject.prototype.revalidate = function() {
    this._info.x = parseInt(this._$node.css("left"), 10);
    this._info.y = parseInt(this._$node.css("top"), 10);
}

GameObject.prototype.setBorder = function(state) {
    if(state === true) {
        this._$node.css("padding", "0px");
        this._$node.css("border", "1px solid black");

    } else {
        this._$node.css("padding", "1px");
        this._$node.css("border", "1px none black");
    }
}

GameObject.prototype.mouseover = function() {
    this.setBorder(true);
}

GameObject.prototype.mouseout = function() {
    this.setBorder(false);
}

GameObject.prototype.clone = function() {
    var info = JSON.parse(JSON.stringify(this._info));
    info.x = parseInt(this._$node.css("left"), 10) + 5;
    info.y = parseInt(this._$node.css("top"), 10) + 5;

    window.editor.register(new GameObject(info));
}

GameObject.prototype.loadNode = function() {
    this._$node = $('<div class="gameobject"></div>');

    var image = "url(/images/" + this._info["type"] + ".png)";
    this._$node.css("background-image", image);
    this._$node.css("width", this._info.width + "px");
    this._$node.css("height", this._info.height + "px");
    this._$node.css("left", this._info.x + "px");
    this._$node.css("top", this._info.y + "px");

     $("body").append(this._$node);

    this._$node.draggable();


    this._$node.mouseover(function () {
        this.mouseover();
    }.bind(this));
    this._$node.mouseout(function () {
        this.mouseout();
    }.bind(this));

    this._$node.mousedown(function(event) {

        switch (event.which) {
            case 3:
                this.clone();
                break;
            default:
                this._clickX = event.clientX;
                this._clickY = event.clientY;
                this._isMouseDown = true;
        }
    }.bind(this));

    this._$node.bind("contextmenu", function(event) {
        return false;
    });

};