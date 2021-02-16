
# Tennis

This is my implementation of the classic tennis game.
I tryed to do it an OOP way, where every game object has all the logic it needs attached to it. But without proper object managment this got very messy, especially on the ball object. A Much better solution would have been to do all the logic in the Tennis.hx file. 


### building

`haxe Tennis.hxml`

This producess a `tennis.js` file in the out directory. In the out directory is also a `index.html` file

### run
Host the out directory on a http-server and open it in a browser.
