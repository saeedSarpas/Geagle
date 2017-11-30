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

     function read_eagle_dset_i(file_path, ptype, dset_name, dtype_id, buf, &
          dest_info, hash) bind(C, name="read_eagle_dset")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: file_path
       integer(kind=c_int), value, intent(in) :: ptype
       character(len=1, kind=c_char), dimension(*), intent(in) :: dset_name
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf, dest_info, hash
       integer(kind=c_int) :: read_eagle_dset_i
     end function read_eagle_dset_i

     function count_particles_i(file_path, hash, nparts) bind(C, name="count_particles")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: file_path
       type(c_ptr), value, intent(in) :: hash, nparts
       integer(kind=c_int) :: count_particles_i
     end function count_particles_i

     function crop_eagle_i(hash, x, y, z, dx, dy, dz) bind(C, name="crop_eagle")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       type(c_ptr), value, intent(in) :: hash
       real(c_double), value :: x, y, z, dx, dy, dz
       integer(c_int) :: crop_eagle_i
     end function crop_eagle_i

     function init_hash_i(file_path, hash) bind(C, name="init_hash")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       character(len=1, kind=c_char), dimension(*), intent(in) :: file_path
       type(c_ptr), value, intent(in) :: hash
       integer(kind=c_int) :: init_hash_i
     end function init_hash_i

     function peano_hilbert_key_i(i, j, k, bits) bind(C, name="peano_hilbert_key")
       use hdf5
       use eagle_types
       use iso_c_binding
       implicit none
       integer(kind=c_int), value :: i, j, k, bits
       integer(kind=c_long_long) :: peano_hilbert_key_i
     end function peano_hilbert_key_i
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
    integer, intent(inout), optional :: status

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


  subroutine read_eagle_dset_1d_f(file_path, ptype, dset_name, dtype_id, buf, &
       err, dset_info, hash)
    implicit none
    character(len=*), intent(in) :: file_path
    integer :: ptype
    character(len=*), intent(in) :: dset_name
    integer(hid_t), value, intent(in) :: dtype_id
    class(*), dimension(:), target :: buf
    integer, optional :: err
    type(eagle_dset_info_t), target, optional :: dset_info
    type(eagle_hash_t), target, optional :: hash

    type(c_ptr) :: buf_p, dset_info_p, hash_p

    if (present(dset_info)) then
       dset_info_p = c_loc(dset_info)
    else
       dset_info_p = c_null_ptr
    end if

    if(present(hash)) then
       hash_p = c_loc(hash)
    else
       hash_p = c_null_ptr
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

    err = read_eagle_dset_i(trim(file_path)//c_null_char, ptype, &
         trim(dset_name)//c_null_char, dtype_id, buf_p, dset_info_p, hash_p)
  end subroutine read_eagle_dset_1d_f


  subroutine read_eagle_dset_2d_f(file_path, ptype, dset_name, dtype_id, buf, &
       err, dset_info, hash)
    implicit none
    character(len=*), intent(in) :: file_path
    integer :: ptype
    character(len=*), intent(in) :: dset_name
    integer(hid_t), value, intent(in) :: dtype_id
    class(*), dimension(:,:), target :: buf
    integer, optional :: err
    type(eagle_dset_info_t), target, optional :: dset_info
    type(eagle_hash_t), target, optional :: hash

    type(c_ptr) :: buf_p, dset_info_p, hash_p

    if (present(dset_info)) then
       dset_info_p = c_loc(dset_info)
    else
       dset_info_p = c_null_ptr
    end if

    if(present(hash)) then
       hash_p = c_loc(hash)
    else
       hash_p = c_null_ptr
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

    err = read_eagle_dset_i(trim(file_path)//c_null_char, ptype, &
         trim(dset_name)//c_null_char, dtype_id, buf_p, dset_info_p, hash_p)
  end subroutine read_eagle_dset_2d_f


  subroutine count_particles_f(file_path, hash, nparts, err)
    implicit none
    character(len=*), intent(in) :: file_path
    type(eagle_hash_t), target :: hash
    integer(kind=c_long_long), target, dimension(:) :: nparts
    integer, optional :: err

    type(c_ptr) :: hash_p, nparts_p

    hash_p = c_loc(hash)
    nparts_p = c_loc(nparts(1))

    err = count_particles_i(trim(file_path)//c_null_char, hash_p, nparts_p)
  end subroutine count_particles_f


  subroutine crop_eagle_f(hash, x, y, z, dx, dy, dz, err)
    implicit none
    type(eagle_hash_t), target :: hash
    real(kind=8) :: x, y, z, dx, dy, dz
    integer, optional :: err

    type(c_ptr) :: hash_p

    hash_p = c_loc(hash)

    err = crop_eagle_i(hash_p, x, y, z, dx, dy, dz)
  end subroutine crop_eagle_f


  subroutine init_hash_f(file_path, hash, err)
    implicit none
    character(len=*), intent(in) :: file_path
    type(eagle_hash_t), target :: hash
    integer, optional :: err

    type(c_ptr) :: hash_p

    hash_p = c_loc(hash)

    err = init_hash_i(trim(file_path)//c_null_char, hash_p)

    ! For accessing allocated arrays, use:
    ! integer(c_int), dimension(:), pointer :: allocated_arr_fp
    ! call c_f_pointer(c_allocated_arr, allocated_arr_fp, shape=[hash%map_len])
  end subroutine init_hash_f


  subroutine peano_hilbert_key_f(i, j, k, bits, err)
    implicit none
    integer :: i, j, k, bits
    integer(kind=8), optional :: err

    err = peano_hilbert_key_i(i, j, k, bits)
  end subroutine peano_hilbert_key_f
end module Geagle
