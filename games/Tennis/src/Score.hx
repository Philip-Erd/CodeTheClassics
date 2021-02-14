

class Score extends h2d.Object {
    
    var p1Score = 0;
    var p2Score = 0;

    var gfx:h2d.Text;

    var scene:h2d.Scene;

    public function new(scene:h2d.Scene){
        super();
        this.scene = scene;

        resize();

        gfx = new h2d.Text(hxd.res.DefaultFont.get(), this);
        gfx.textAlign = Center;

        updateGfx();
    }


    private function updateGfx(){
        gfx.text = p1Score + " : " + p2Score;
    }

    //if player one scored
    public function p1Scored(){
        p1Score += 1;
        //update the graphics
        updateGfx();
    }

    //if player two scored
    public function p2Scored(){
        p2Score += 1;
        //update the graphics
        updateGfx();
    }

    public function resize(){
        this.setScale(scene.width * 0.005);
    }
}