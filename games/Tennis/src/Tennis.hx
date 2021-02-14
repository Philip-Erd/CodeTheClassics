import hxd.Window;

class Tennis extends hxd.App {

    //objects
    var player1:Player;
    var player2:Player;
    var score:Score;
    var ball:Ball;




    override function init() {

        //initialze players and ball
        player1 = new Player(1, s2d);
        player2 = new Player(2, s2d);
        score = new Score();
        ball = new Ball(player1, player2, s2d, score);

        //add all to scene 2d
        s2d.addChild(player1);
        s2d.addChild(player2);
        s2d.addChild(score);
        s2d.addChild(ball);

        //set the initial position of all three objects
        ball.setPosition(s2d.width/2, s2d.height/2);
        player1.setPosition(20, s2d.height/2); //left side player
        player2.setPosition(s2d.width -20, s2d.height/2); //right side player

        //setup score
        score.setPosition(s2d.width/2, 10);
        score.setScale(3);

        //playfield
        var field = new h2d.Graphics(s2d);
        field.setPosition(0, 0);
        field.lineStyle(2, 0xFFFFFFFF);
        field.lineTo(0,0);
        field.lineTo(s2d.width, 0);
        field.lineTo(s2d.width, s2d.height);
        field.lineTo(0, s2d.height);
        field.lineTo(0,0);
        
    }

    override function update(dt:Float) {

        //updating players
        player1.update(dt);
        player2.update(dt);

        //updating the ball
        ball.update(dt);
    }


}
