_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]
assert( require 'premake.quickstart' )

local function demo_dirs()
	local res={}
	for dir in io.popen([[dir "demo*" /b /ad]]):lines() do res[#res+1] = dir end
	return res
end

local function make_demo(dir)
	make_console_app( dir, path.join(path.join('.',dir),'**.cpp') )
	links { 'libsttcl' }
	make_cpp11()
	--run_target_after_build()
end

make_solution 'sttcl'

includedirs { './sttcl/include' }

defines {
	'STTCL_CX11_TIME',
	'STTCL_CX11_THREADS',
	'STTCL_CX11_SEMAPHORE'
}

make_static_lib ( 'libsttcl' , {
		path.join('./sttcl/C++11Threads','**.cpp'),
		path.join('./sttcl/C++11Time','**.cpp')
	}
)

for _,dir in ipairs(demo_dirs()) do
	print(dir)
	make_demo(dir)
end
