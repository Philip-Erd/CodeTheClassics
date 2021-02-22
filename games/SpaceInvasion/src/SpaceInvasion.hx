import h2d.Graphics;


class SpaceInvasion extends hxd.App{

    private var player:h2d.Object;

    //aliens 4 rows and 8 collums
    private var aliens:Array<h2d.Object>;
    private var alienRows = 4;
    private var alienCol = 8;

    override function init() {
        super.init();

        //create player
        player = new h2d.Object(s2d);
        var playerGfx = new h2d.Graphics(player);
        playerGfx.beginFill(0xFFFFFFFF);
        playerGfx.drawRect(-5, -5, 10, 10);
        playerGfx.endFill();

        player.setPosition(s2d.width/2, s2d.height -20);



        //Create Aliens
        aliens = new Array<h2d.Object>();

        for(x in 0...alienCol){
            for(y in 0...alienRows){
                var alien = new h2d.Object(s2d);
                var alienGfx = new Graphics(alien);
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
    }
}