module Geagle
  use hdf5
  use eagle_types
  implicit none

  interface
     function open_eagle_i(fpath, eagle) bind(C, name="open_eagle")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: fpath
       type(c_ptr), value, intent(in) :: eagle
       integer(kind=c_int) :: open_eagle_i
     end function open_eagle_i

     function read_eagle_dset_i(file_id, dset_name, dtype_id, buf, dest_info) &
          bind (C, name="read_eagle_dset")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       integer(kind=c_int), value, intent(in) :: file_id
       character(len=1, kind=c_char), dimension(*), intent(in) :: dset_name
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf, dest_info
       integer(kind=c_int) :: read_eagle_dset_i
     end function read_eagle_dset_i
  end interface


contains
  subroutine open_eagle_f(fpath, eagle_o, file_id)
    implicit none
    character(len=*), intent(in) :: fpath
    type(eagle_t), target :: eagle_o
    integer(hid_t), intent(out), optional :: file_id

    type(c_ptr) :: eagle_p

    integer(hid_t) :: h5err

    call H5open_f(h5err)

    if (h5err < 0) then
       print *, "[ERROR] Unable to initialize HDF5"
       stop
    end if

    eagle_p = c_loc(eagle_o)

    file_id = open_eagle_i(trim(fpath)//c_null_char, eagle_p)
  end subroutine open_eagle_f

  subroutine read_eagle_dset_f(file_id, dset_name, dtype_id, buf, err, dset_info)
    implicit none
    integer(hid_t), value, intent(in) :: file_id
    character(len=*), intent(in) :: dset_name
    integer(hid_t), value, intent(in) :: dtype_id
    class(*), dimension(:), target :: buf
    integer(kind=4), intent(out), optional :: err
    type(eagle_dset_info_t), target, optional :: dset_info

    type(c_ptr) :: buf_p
    type(c_ptr) :: dset_info_p

    if (present(dset_info)) then
       dset_info_p = c_loc(dset_info)
    else
       dset_info_p = c_null_ptr
    end if

    ! c_loc doesn't accept a polymorphic variable. Following is an attempt to
    ! overcome this problem
    select type(buf)
    type is (integer(kind=4))
       buf_p = c_loc(buf(1))
    type is (integer(kind=8))
       buf_p = c_loc(buf(1))
    type is (real(kind=4))
       buf_p = c_loc(buf(1))
    type is (real(kind=8))
       buf_p = c_loc(buf(1))
    end select

    err = read_eagle_dset_i(file_id, trim(dset_name)//c_null_char, dtype_id, &
         buf_p, dset_info_p)
  end subroutine read_eagle_dset_f
end module Geagle
