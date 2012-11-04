
function Editor() {
    this._objects = [];
    window.editor = this; // TEEHEE global :D

    setInterval(function() {
        this.save();
    }.bind(this), 1000);
}

Editor.prototype.load = function(json) {
    for(var k in json.dynamic) {
        window.editor.register(new GameObject(json.dynamic[k]));
    }
};

Editor.prototype.register = function(gameobject) {
    this._objects.push(gameobject);
}


Editor.prototype.save = function() {
    var json = {
        "dynamic" : []
    };

    for(var k in this._objects) {
        this._objects[k].revalidate();

        json.dynamic.push(this._objects[k]._info);
    }

    $.post(window.location, { "newdata" : JSON.stringify(json) });

    console.log(json);
}