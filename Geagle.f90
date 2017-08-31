module Geagle
  use hdf5
  use eagle_types
  implicit none

  interface
     function init_eagle_i(fpath, eagle) bind(C, name="init_eagle")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: fpath
       type(c_ptr), value, intent(in) :: eagle
       integer(kind=c_int) :: init_eagle_i
     end function init_eagle_i

     function read_eagle_dset_i(file_path, p_type, dset_name, dtype_id, buf, &
          dest_info) bind (C, name="read_eagle_dset")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: file_path
       integer(kind=c_int), value, intent(in) :: p_type
       character(len=1, kind=c_char), dimension(*), intent(in) :: dset_name
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf, dest_info
       integer(kind=c_int) :: read_eagle_dset_i
     end function read_eagle_dset_i
  end interface

  interface read_eagle_dset_f
     module procedure read_eagle_dset_1d_f
     module procedure read_eagle_dset_2d_f
  end interface read_eagle_dset_f


contains
  subroutine init_eagle_f(fpath, eagle_o, status)
    implicit none
    character(len=*), intent(in) :: fpath
    type(eagle_t), target :: eagle_o
    integer, intent(out), optional :: status

    type(c_ptr) :: eagle_p

    integer(hid_t) :: h5err

    call H5open_f(h5err)

    if (h5err < 0) then
       print *, "[ERROR] Unable to initialize HDF5"
       stop
    end if

    eagle_p = c_loc(eagle_o)

    status = init_eagle_i(trim(fpath)//c_null_char, eagle_p)
  end subroutine init_eagle_f


  subroutine read_eagle_dset_1d_f(file_path, p_type, dset_name, dtype_id, buf, &
       err, dset_info)
    implicit none
    character(len=*), intent(in) :: file_path
    integer :: p_type
    character(len=*), intent(in) :: dset_name
    integer(hid_t), value, intent(in) :: dtype_id
    class(*), dimension(:), target :: buf
    integer, optional :: err
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

    err = read_eagle_dset_i(trim(file_path)//c_null_char, p_type, &
         trim(dset_name)//c_null_char, dtype_id, buf_p, dset_info_p)
  end subroutine read_eagle_dset_1d_f


  subroutine read_eagle_dset_2d_f(file_path, p_type, dset_name, dtype_id, buf, &
       err, dset_info)
    implicit none
    character(len=*), intent(in) :: file_path
    integer :: p_type
    character(len=*), intent(in) :: dset_name
    integer(hid_t), value, intent(in) :: dtype_id
    class(*), dimension(:,:), target :: buf
    integer, optional :: err
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
       buf_p = c_loc(buf(1,1))
    type is (integer(kind=8))
       buf_p = c_loc(buf(1,1))
    type is (real(kind=4))
       buf_p = c_loc(buf(1,1))
    type is (real(kind=8))
       buf_p = c_loc(buf(1,1))
    end select

    err = read_eagle_dset_i(trim(file_path)//c_null_char, p_type, &
         trim(dset_name)//c_null_char, dtype_id, buf_p, dset_info_p)
  end subroutine read_eagle_dset_2d_f
end module Geagle
