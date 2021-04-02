pico-8 cartridge // http://www.pico-8.com
version 32
__lua__
orig1 = peek4(0x5f00)
orig2 = peek4(0x5f04)
orig3 = peek4(0x5f08)
orig4 = peek4(0x5f0c)
cartdata("dummy")

function set_layer(top)
	if top then
		poke4(0x5f00,0x0e00.0180)
		poke4(0x5f04,0x0e00.0180)
		poke4(0x5f08,0x0e00.0180)
		poke4(0x5f0c,0x0e00.0180)
	else
		poke4(0x5f00,0x8080.8080)
		poke4(0x5f04,0x0101.0101)
		poke4(0x5f08,0x0000.0000)
		poke4(0x5f0c,0x0e0e.0e0e)
	end
end

function _draw()
 cls()
 color(15)
 
 print(orig1,15)
	print(orig2,15)
	print(orig3,15)
	print(orig4,15)

 print("")
 set_layer(true)
 
	print(peek4(0x5f00))
	print(peek4(0x5f04))
	print(peek4(0x5f08))
	print(peek4(0x5f0c))

	print("")
 set_layer(false)
 
 print(peek4(0x5f00))
	print(peek4(0x5f04))
	print(peek4(0x5f08))
	print(peek4(0x5f0c))


 print("")
 poke4(0x5e00,0x0ef0.0189)

 print(peek4(0x5e00))
 print(dget(0))

end
__gfx__
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00700700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00077000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00077000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00700700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
