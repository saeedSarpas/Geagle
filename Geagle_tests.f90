program Geagle_tests
  use HDF5
  use Geagle
  use eagle_types
  implicit none

  integer :: status
  type(eagle_t) :: eagle_o
  real(kind=4), allocatable :: hydrogen(:), coordinates(:,:)
  integer :: i, err, n, n1
  type(eagle_hash_t), target :: hash
  integer(c_int), dimension(:), pointer :: map_fp
  real(kind=8) :: origin, len, half
  integer(c_long_long), dimension(6) :: nparts
  type(eagle_dset_info_t), target :: dset_info

  call init_eagle_f("./snapshot/eagle_snap.%d.hdf5", eagle_o, status)
  print *, "status: ", status

  call init_hash_f("./snapshot/eagle_snap.%d.hdf5", hash, err)
  call c_f_pointer(hash%map, map_fp, shape=[hash%map_len])
  ! print *, "err:", err
  ! print *, hash%map_len, hash%bits, hash%num_files, hash%box_size, map_fp(1), &
  !      map_fp(hash%map_len)

  origin = 0.0
  half = hash%box_size / 2.0
  call crop_eagle_f(hash, origin, origin, origin, half, half ,half, err)
  ! print *, hash%map_len, hash%bits, hash%num_files, hash%box_size, map_fp(1), &
  !      map_fp(hash%map_len)
  call count_particles_f("./snapshot/eagle_snap.%d.hdf5", hash, nparts, err)
  print *, nparts

  ! n = eagle_o%header%NumPart_Total(5)
  ! n1 = eagle_o%header%NumPart_ThisFile(5)
  n = nparts(5)
  allocate(hydrogen(n))
  allocate(coordinates(3, n))

  call read_eagle_dset_1d_f("./snapshot/eagle_snap.%d.hdf5", star_particles, &
       "ElementAbundance/Hydrogen", H5T_NATIVE_REAL_4, hydrogen, dset_info, hash, err)

  ! print *, hydrogen(1), " = 0.7514407"
  ! print *, hydrogen(2), " = 0.752"
  ! print *, hydrogen(3), " = 0.74708647"
  ! print *, hydrogen(4), " = 0.752"
  ! print *, hydrogen(5), " = 0.75119805"
  ! print *, hydrogen(6), " = 0.752"
  ! print *, hydrogen(7), " = 0.752"
  ! print *, hydrogen(8), " = 0.7491258"
  ! print *, hydrogen(9), " = 0.75045615"
  ! print *, hydrogen(10), " = 0.7519901"
  ! print *, hydrogen(11), " = 0.7517845"
  ! print *, hydrogen(12), " = 0.7485215"
  ! print *, hydrogen(13), " = 0.7493876"
  ! print *, hydrogen(14), " = 0.7483244"
  ! print *, hydrogen(15), " = 0.75086343"
  ! print *, hydrogen(16), " = 0.749952"
  ! print *, hydrogen(17), " = 0.752"
  ! print *, hydrogen(18), " = 0.7514676"
  ! print *, hydrogen(19), " = 0.75032496"
  ! print *, hydrogen(20), " = 0.7470617"

  do i=1, n
     print *, i, hydrogen(i)
  end do

  ! call read_eagle_dset_f("./snapshot/eagle_snap.%d.hdf5", star_particles, &
  !      "Coordinates", H5T_NATIVE_REAL_4, coordinates, dset_info, hash, err)

  ! print *, &
  !      coordinates(1,1), "= 0.1309898002426685,", &
  !      coordinates(2,1), "= 0.24455139258558567,", &
  !      coordinates(3,1), "= 0.7794424644906142"
  ! print *, &
  !      coordinates(1,2), "= 0.13102883110411634,", &
  !      coordinates(2,2), "= 0.09255978939225869,", &
  !      coordinates(3,2), "= 0.7607126429028089"
  ! print *, &
  !      coordinates(1,3), "= 0.049672847061444855,", &
  !      coordinates(2,3), "= 0.5268933353582979,", &
  !      coordinates(3,3), "= 0.830702932358309"
  ! print *, &
  !      coordinates(1,n1), "= 0 013948121149788998,", &
  !      coordinates(2,n), "= 6.158768858638972,", &
  !      coordinates(3,n), "= 0.7320701547859704"

  ! do i=1, n
  !    print *, i, coordinates(:,i)
  ! end do

  ! deallocate(hydrogen)
  ! allocate(hydrogen(nparts(star_particles+1)))

  ! call read_eagle_dset_f("./snapshot/eagle_snap.%d.hdf5", star_particles, &
  !      "ElementAbundance/Hydrogen", H5T_NATIVE_REAL_4, hydrogen, err, dset_info, hash)

  ! print *, dset_info%aexp_scale_exponent, dset_info%h_scale_exponent, dset_info%CGSConversionFactor, &
  !      dset_info%VarDescription
  ! print *, hydrogen(10), hydrogen(nparts(star_particles+1))

end program Geagle_tests
