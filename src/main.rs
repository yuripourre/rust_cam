mod v4l {
      
    #[link(name = "v4l-rust")]
    extern {
        fn open_device(device_name: &str) -> i64;
    }

    pub fn rust_open_device(device_name: &str) -> i64 {
        unsafe {
            open_device(device_name)
        }
    }
}

fn main() -> () {
    println!("{}", v4l::rust_open_device("/dev/video0"));
}
