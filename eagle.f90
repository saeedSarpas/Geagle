module Eagle
  use hdf5
  use eagle_types
  implicit none

  interface
     function open_eagle_i(fpath, eagle) bind(C, name="open_eagle")
       use hdf5
       use eagle_types
       use iso_c_binding
       character(len=1, kind=c_char), dimension(*), intent(in) :: fpath
       type(c_ptr), value, intent(in) :: eagle
       integer(kind=c_int) :: open_eagle_i
     end function open_eagle_i
  end interface


contains
  subroutine open_eagle_f(fpath, eagle_o, file_id)
    character(len=*), intent(in) :: fpath
    type(eagle_t), target :: eagle_o
    integer(hid_t), intent(out), optional :: file_id

    type(c_ptr) :: eagle_p

    eagle_p = c_loc(eagle_o)

    file_id = open_eagle_i(trim(fpath)//c_null_char, eagle_p)
  end subroutine open_eagle_f
end module Eagle
