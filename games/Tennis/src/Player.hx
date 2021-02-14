

class Player extends h2d.Object {

    private var speed = 200;

    private var gfx:h2d.Graphics;
    private var scene:h2d.Scene; //used for clamping the the paddles to the screen dimensions

    private var keyUp:Int;
    private var keyDown:Int;

    public var width = 10;
    public var height = 60;
    public var moveV = 0;



    public function new(playerNumber: Int, scene:h2d.Scene){
        super();
        this.scene = scene;

        //assining the proper keys
        if(playerNumber == 1){
            keyUp = hxd.Key.W;
            keyDown = hxd.Key.S;
        }else{
            keyUp = hxd.Key.UP;
            keyDown = hxd.Key.DOWN;
        }

        //add graphics
        gfx = new h2d.Graphics(this);
        gfx.beginFill(0xFFFFFFFF);
        gfx.drawRect(-width/2, -height/2, width, height);
        gfx.endFill();
    }


    public function update(dt:Float){

        moveV = 0;
        //p1 uses "w" and "S"
        if(hxd.Key.isDown(keyUp)){
            //move up
            moveV -= 1;
        }

        if(hxd.Key.isDown(keyDown)){
            //move down
            moveV += 1;
        }

        //look rough, but it only adds the move value (multiplied by the speed and dt)
        //to the current y position and clamps it between the screen size
        y = Math.min(Math.max(height /2, y + (moveV * speed * dt)), scene.height - (height /2));
    }



}