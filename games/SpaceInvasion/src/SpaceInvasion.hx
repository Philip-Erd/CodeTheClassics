


class SpaceInvasion extends hxd.App{

    private var gameOver = false;
    private var gameOverText:h2d.Text;

    private var player:h2d.Object;
    private var playerSpeed = 200;

    private var bullet:h2d.Graphics;
    private var bulletSpeed = 400;
    private var readyToShoot = true;        //The same bullet is used again so the player is only allowed to shoot
                                            //if the bullet is out of the screen or had hit an alien

    //aliens 4 rows and 8 collums
    private var aliens:Array<h2d.Object>;
    private var alienRows = 4;
    private var alienCol = 8;
    private var alienLeftMostPosition:Int;      //How far to the left do the aliens travel
    private var alienRightMostPosition:Int;     //How far to the right do the aliens travel
    private var alienVerticalLimit:Int;         //How far can the aliens go down before game over
    private var alienSpeed = 50;                //Move speed of aliens (negative move left, positive move right)
    private var alienVerticalSpeed = 10;

    override function init() {
        super.init();

        alienLeftMostPosition = 10;
        alienRightMostPosition = s2d.width -10;
        alienVerticalLimit = s2d.height -50;

        //boarder
        var field = new h2d.Graphics(s2d);
        field.setPosition(0, 0);
		field.lineStyle(2, 0xFFFFFFFF);
		field.lineTo(0, 0);
		field.lineTo(s2d.width, 0);
		field.lineTo(s2d.width, s2d.height);
		field.lineTo(0, s2d.height);
		field.lineTo(0, 0);

        //create player
        player = new h2d.Object(s2d);
        var playerGfx = new h2d.Graphics(player);
        playerGfx.beginFill(0xFFFFFFFF);
        playerGfx.drawRect(-5, -5, 10, 10);
        playerGfx.endFill();

        player.setPosition(s2d.width/2, s2d.height -20);


        //create bullet
        bullet = new h2d.Graphics(s2d);
        bullet.beginFill(0xFFFFFFFF);
        bullet.drawCircle(0, 0, 2, 8);
        bullet.endFill();
        bullet.setPosition(-10, -10);   //set it out of visible space;


        //create game over Text
        gameOverText = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
        gameOverText.textAlign = Center;
        gameOverText.setScale(10);
        gameOverText.text = "GAME OVER";
        gameOverText.setPosition(s2d.width/2, 50);
        gameOverText.visible = false;                           //hide at startup;




        //Create Aliens
        aliens = new Array<h2d.Object>();

        for(x in 0...alienCol){
            for(y in 0...alienRows){
                var alien = new h2d.Object(s2d);
                var alienGfx = new h2d.Graphics(alien);
                alienGfx.beginFill(0xFFFFFFFF);
                alienGfx.drawCircle(0, 0, 10, 8);
                alienGfx.endFill();
                var px = ((s2d.width - 50) / alienCol) * x + 50;
                var py = ((s2d.height - 200) / alienRows) * y + 20;
                alien.setPosition(px, py);

                aliens.insert(x + (y*alienCol), alien);
            }
        }

    }

    override function update(dt:Float) {
        super.update(dt);


        //update Aliens
        var atBoundary = false;                  //see if left or right most position is reached
        for(alien in aliens){
            alien.setPosition(alien.x + alienSpeed * dt, alien.y);

            //horizontal limit
            if(!atBoundary){
                if((alien.x > alienRightMostPosition) || (alien.x < alienLeftMostPosition)){
                    atBoundary = true;
                }
            }
        }
        
        //atBoundars check
        if(atBoundary){

            atBoundary = false;             //reused for vertical limit
            alienSpeed = -alienSpeed;
            //move aliens down
            for(alien in aliens){
                alien.setPosition(alien.x, alien.y + alienVerticalSpeed);

                //vertical limit
                if(!atBoundary){
                    if(alien.y > alienVerticalLimit){
                        gameOver = true;
                        atBoundary = true;
                    }
                }
            }
        }


        //Move player
        //left
        if(hxd.Key.isDown(hxd.Key.A) || hxd.Key.isDown(hxd.Key.LEFT)){
            //limit player travel distance
            if(player.x > 10){
                player.setPosition(player.x - playerSpeed * dt, player.y);
            }
        }

        //right
        if(hxd.Key.isDown(hxd.Key.D) || hxd.Key.isDown(hxd.Key.RIGHT)){
            //limit player travel distance
            if(player.x < s2d.width - 10){
                player.setPosition(player.x + playerSpeed * dt, player.y);
            }
        }

        //shoot
        if(hxd.Key.isPressed(hxd.Key.SPACE) && readyToShoot){
            readyToShoot = false;
            bullet.setPosition(player.x, player.y -5);
        }

        //bullet

        //only update if bullet is used
        if(!readyToShoot){
            bullet.setPosition(bullet.x, bullet.y - bulletSpeed * dt);

            //bullet alien collision
            for(alien in aliens){
                if(bulletAlienCollision(alien, bullet)){
                    removeAlien(alien);
                    readyToShoot = true;
                    bullet.setPosition(-10, -10);
                }
            }
            

            //screen space end
            if(bullet.y < 0){
                readyToShoot = true;
                bullet.setPosition(-10, -10);   //set it in to the wild
            }
        }


        //game over check
        if(gameOver){
            gameOverText.visible = true;
        }
    }


    private function bulletAlienCollision(alien:h2d.Object, bullet:h2d.Object):Bool {
        var x = alien.x - bullet.x;
        var y = alien.y - bullet.y;
        var d = Math.sqrt(x*x + y*y);
        
        if(d < 10){
            return true;
        }else{
            return false;
        }
    }

    private function removeAlien(alien:h2d.Object){
        alien.visible = false;
        aliens.remove(alien);
        

        //show win message (reusing game over text)
        if(aliens.length == 0){
            gameOverText.text = "YOU WIN";
            gameOver  = true;
        }
    }
}