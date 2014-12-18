all: rust_cam

rust_cam:
	gcc -shared -o libv4l-rust.so rust_cam.c -fPIC
	cp libv4l-rust.so ../

bin:
	gcc -o rust_cam rust_cam.c -fPIC
