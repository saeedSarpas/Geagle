module Eagle
  implicit none

  interface
     function open_eagle(fpath, eagle) bind(C, name="open_eagle")
       use HDF5
       use eagle_types
       use iso_c_binding
       character(len=1, kind=c_char), dimension(*), intent(in) :: fpath
       type(c_ptr), value, intent(in) :: eagle
       integer(hid_t) :: open_eagle
     end function open_eagle
  end interface
end module Eagle
