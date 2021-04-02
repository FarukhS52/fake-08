pico-8 cartridge // http://www.pico-8.com
version 29
__lua__
function brd(f)
 apal(2)
 camera(-1,0) f()
 camera(1,0) f()
 camera(0,-1) f()
 camera(0,1) f()
 pal()
 camera() f()
end

function apal(n)
 for i=0,15 do pal(i,n) end
end


function _draw()
	cls(10)
	
	local s="press ❎ to start"
 function f()
  print(s,64-2*#s,88,15)
 end
 brd(f)

end

__gfx__
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00700700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00077000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00077000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00700700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
