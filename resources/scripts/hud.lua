

 hud_life_pos_x = 0
 hud_life_pos_y = 130
 
 
 hud_offset_width =  _getWidth()
 hud_offset_height = _getHeight()

hud_pos_x = 0
hus_pos_y =  (hud_offset_height - 32) - 1



function  init(host)
    _createHud(host, 0, (hud_offset_height - 32) - 1, hud_offset_width, hud_offset_height)
    _setLivesPosition(host,  hud_life_pos_x,  hud_life_pos_y)
end

function destroy(host)
    print "---- END OF hud.lua ----"
end

