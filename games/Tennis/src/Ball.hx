import h2d.Graphics;

class Ball extends h2d.Object {

    private var gfx:h2d.Graphics;
    private var velocity:h3d.Vector; //we only use x and y here
    private var estimatedPosition:h3d.Vector; //used for collision detection
    private var speed = 150; //The speed of the ball

    private var radius = 5; //the radius of the ball

    private var p1:Player; //The object for Player1
    private var p2:Player; //The object for Player2
    private var scene:h2d.Scene; //The current scene (used for edge collision)
    private var score:Score;

    public function new(p1:Player, p2:Player, scene:h2d.Scene, score:Score){
        super();

        //this. is used to prevent name collision
        this.p1 = p1;
        this.p2 = p2;
        this.scene = scene;
        this.score = score;

        //add graphics
        gfx = new Graphics(this);
        gfx.beginFill(0xFFFFFFFF);
        gfx.drawCircle(0, 0, radius, 16);
        gfx.endFill();

        //initializing the velocity
        //The ball has only 6 direction(no direct up or down), so (1, 1) means down right.
        //This can be randomized, but I dont care for now.
        velocity = new h3d.Vector(1, 1);

        estimatedPosition = new h3d.Vector();
    }

    public function update(dt:Float){

        //updating ball position
        //This is usualy done in a seperate physics update loop with a fixed update time
        //Doing this in normal update requieres the use of the delta time (dt) to get
        //a consistent speed;
        estimatedPosition.x = x + (velocity.x * speed * dt);
        estimatedPosition.y = y + (velocity.y * speed * dt);


        //collision detection

        //Left edge
        if((x - radius) <= 0){
            //score p2
            score.p2Scored();
            
            //set to center
            setPosition(scene.width/2, scene.height/2);
            velocity.x = 1; //move towards other player
        }

        //Right edge
        if((x + radius) >= scene.width){
            //score p1
            score.p1Scored();
            //set to center
            setPosition(scene.width/2, scene.height/2);
            velocity.x = -1; //move towards other player
        }

        //bottom edge
        if((y + radius) >= scene.height){
            //invert y velocity
            velocity.y = -velocity.y;
        }
        //top edge
        if((y - radius) <= 0){
            //invert y velocity
            velocity.y = -velocity.y;
        }

        //The player collision detection is a lot, but actualy point inside rect collision
        //with some radius. It doesn even check the coplete rect (back is missing)

        //p1
        if(((x - radius) < (p1.x + (p1.width /2))) && ((y) > (p1.y - (p1.height/2))) && ((y) < (p1.y + (p1.height/2)))){
            velocity.x = 1; //flipping direction

            //enables paddle to kick ball in moving direction
            if(p1.moveV > 0){
                velocity.y = 1;
            }else if(p1.moveV < 0){
                velocity.y = -1;
            }
        }

        //p2
        if((((x + radius) > (p2.x - (p2.width/2)))) && (y > (p2.y - (p2.height/2))) && (y < (p2.y + (p2.height/2)))){
            velocity.x = -1; //flipping direction

            //enables paddle to kick ball in moving direction
            if(p2.moveV > 0){
                velocity.y = 1;
            }else if(p2.moveV < 0){
                velocity.y = -1;
            }
        }

        //update position
        x = x + (velocity.x * speed * dt);
        y = y + (velocity.y * speed * dt);
    }
    
}