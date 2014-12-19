mod v4l {
      
    #[link(name = "v4l-rust")]
    extern {
        fn v4l_open_device(device_name: &str) -> i32;
        fn v4l_open_first_device() -> i32;
        fn v4l_close_device(device: i32) -> i32;
        fn v4l_print_caps(fd: i32) -> i32;
        fn v4l_init_mmap(fd: i32) -> i32;
        fn v4l_capture_image(fd: i32) -> i32;
    }

    pub fn open_device(device_name: &str) -> i32 {
        unsafe {
            v4l_open_device(device_name)
        }
    }

    pub fn open_first_device() -> i32 {
        unsafe {
            v4l_open_first_device()
        }
    }

    pub fn close_device(device: i32) -> i32 {
        unsafe {
            v4l_close_device(device)
        }
    }

    pub fn print_caps(fd: i32) -> i32 {
        unsafe {
            v4l_print_caps(fd)
        }
    }

    pub fn init_mmap(fd: i32) -> i32 {
        unsafe {
            v4l_init_mmap(fd)
        }
    }

    pub fn capture_image(fd: i32) -> i32 {
        unsafe {
            v4l_capture_image(fd)
        }
    }

}

fn main() -> () {

    let fd = v4l::open_first_device();
    println!("fd = {}", fd);
    
    v4l::print_caps(fd);
        
    v4l::init_mmap(fd);

    for i in range(0i, 5i) {
        if v4l::capture_image(fd) != 0 {
            break;
        }
    }

    v4l::close_device(fd);
}

