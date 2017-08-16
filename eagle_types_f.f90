module eagle_types
  use iso_c_binding

  implicit none

  type, bind(C) :: eagle_header_t
     real(c_double) :: BoxSize, E_z, ExpansionFactor, H_z, HubbleParam, &
          Omega0, OmegaBaryon, OmegaLambda, Redshift, Time, MassTable(6)
     integer(c_int) :: Flag_Cooling, Flag_DoublePrecision, Flag_Feedback, &
          Flag_IC_Info, Flag_Metals, Flag_Sfr, Flag_StellarAge, &
          NumFilesPerSnapshot, NumPart_ThisFile(6), NumPart_Total(6), &
          NumPart_Total_HighWord(6)
     character(len=1, kind=c_char), dimension(256) :: RunLabel;
  end type eagle_header_t

  type, bind(C) :: eagle_units_t
     real(c_double) :: UnitDensity_in_cgs, UnitEnergy_in_cgs, &
          UnitLength_in_cm, UnitMass_in_g, UnitPressure_in_cgs, UnitTime_in_s, &
          UnitVelocity_in_cm_per_s
  end type eagle_units_t

  type, bind(C) :: eagle_constants_t
     real(c_double) :: AVOGADRO, BOLTZMANN, C, CM_PER_MPC, ELECTRONCHARGE, &
          ELECTRONMASS, EV_TO_ERG, GAMMA, GAS_CONST, GRAVITY, HUBBLE, PI, &
          PLANCK, PROTONMASS, RAD_CONST, SEC_PER_MEGAYEAR, SEC_PER_YEAR, &
          SOLAR_LUM, SOLAR_MASS, STEFAN, THOMPSON, T_CMB0, Z_Solar
  end type eagle_constants_t

  type, bind(C) :: eagle_runtime_pars_t
     integer(c_int) :: AGB_EnergyTransferOn, AGB_MassTransferOn, &
          ComovingIntegrationOn, CoolingOn, DesLinkNgb, DesNumNgb, FoFFormat, &
          FoFOutputListOn, Generations, ICFormat, MaxMemSize, MetDepCoolingOn, &
          NumFilesPerSnapshot, NumFilesWrittenInParallel, OutputListOn, &
          PeriodicBoundariesOn, ResubmitOn, SF_THRESH_MaxPhysDensOn, &
          SNII_EnergyTransferOn, SNII_MassTransferOn, SNII_WindIsotropicOn, &
          SNIa_EnergyTransferOn, SNIa_EnergyTransferStochastic, &
          SNIa_MassTransferOn, SmallOutputListOn, SmallOutputTar, SnapFormat, &
          StarformationOn, StellarEnergyFeedbackOn, StellarEvol_FeedbackOn, &
          StellarEvolutionTimestepInterval, StellarMetalFeedbackOn, &
          TypeOfOpeningCriterion, TypeOfTimestepCriterion
     real(c_float) :: ArtBulkViscConst, ArtBulkViscConstMin, ArtDiffConst, &
          ArtDiffConstMin, BHAllocFactor, BH_ConstantHeatTemp, &
          BH_MaxHeatLimit, BH_MaxHeatTemp, BH_MaxMergingDistanceFactor, &
          BH_MaxRepositionDistanceFactor, BH_MinHeatLimit, BH_MinHeatTemp, &
          BH_maxHeatingProbability, BlackHoleAccretionFactor, &
          BlackHoleAccretionSlope, BlackHoleEddingtonFactor, &
          BlackHoleFeedbackFactor, BlackHoleMaxAccretionRadius, &
          BlackHoleNgbFactor, BlackHoleNumberOfNeighboursToHeat, &
          BlackHoleRadiativeEfficiency, BlackHoleViscousAlpha, BoxSize, &
          BufferSize, CalciumOverSilicon, CourantFac, CpuTimeBetRestartFile, &
          DesNumNgbStar, DesNumNgbYoungStar, EOS_Cool_GammaEffective, &
          EOS_Cool_MinOverDens, EOS_Cool_MinPhysDens_HpCM3, &
          EOS_Cool_TempNorm_K, EOS_Jeans_GammaEffective, &
          EOS_Jeans_MinOverDens, EOS_Jeans_MinPhysDens_HpCM3, &
          EOS_Jeans_TempNorm_K, EOS_NormPhysDens_HpCM3, ErrTolForceAcc, &
          ErrTolIntAccuracy, ErrTolTheta, ErrTolThetaSubfind, &
          GravityConstantInternal, HubbleParam, IMF_Exponent, &
          IMF_MaxMass_MSUN, IMF_MinMass_MSUN, InitAbundance_Carbon, &
          InitAbundance_Helium, InitAbundance_Hydrogen, InitAbundance_Iron, &
          InitAbundance_Magnesium, InitAbundance_Neon, InitAbundance_Nitrogen, &
          InitAbundance_Oxygen, InitAbundance_Silicon, InitGasTemp, &
          InitMetallicity, MaxNumNgbDeviation, MaxRMSDisplacementFac, &
          MaxSizeTimestep, MaxSmoothingLengthChange, MetAllocFactor, &
          MinFoFMassForNewSeed_Msun, MinGasHsmlFractional, MinGasTemp, &
          MinSizeTimestep, Omega0, OmegaBaryon, OmegaLambda, PartAllocFactor, &
          REION_H_Heating_EVpH, REION_H_ZCenter, REION_He_Heating_EVpH, &
          REION_He_ZCenter, REION_He_ZSigma, SF_SchmidtLawCoeff_MSUNpYRpKPC2, &
          SF_SchmidtLawExponent, SF_SchmidtLawHighDensExponent, &
          SF_SchmidtLawHighDensThresh_HpCM3, SF_THRESH_MaxPhysDens_HpCM3, &
          SF_THRESH_MetDepSFThreshMaxThresh_HpCM3, &
          SF_THRESH_MetDepSFThreshNorm_HpCM3, SF_THRESH_MetDepSFThreshSlope, &
          SF_THRESH_MinOverDens, SF_THRESH_MinPhysDens_HpCM3, &
          SF_THRESH_TempMargin_DEX, SNII_Delta_T_Divided_By_T_Vir, &
          SNII_Delta_T_K, SNII_Energy_ERG, SNII_Factor_Carbon, &
          SNII_Factor_Helium, SNII_Factor_Hydrogen, SNII_Factor_Iron, &
          SNII_Factor_Magnesium, SNII_Factor_Neon, SNII_Factor_Nitrogen, &
          SNII_Factor_Oxygen, SNII_Factor_Silicon, SNII_MaxEnergyFraction, &
          SNII_MaxMass_MSUN, SNII_Max_Delta_T_K, SNII_MinEnergyFraction, &
          SNII_MinMass_MSUN, SNII_Min_Delta_T_K, SNII_Tvir0_K, &
          SNII_Width_logTvir_dex, SNII_WindDelay_YR, SNII_exponent_Delta_T, &
          SNII_normalisation_Delta_T_K, SNII_rhogas_physdensnormfac, &
          SNII_rhogas_power, SNII_zdep_power, SNIa_Efficiency, &
          SNIa_EjectaVelocity_KMpS, SNIa_EnergyFraction, SNIa_Energy_ERG, &
          SNIa_TimeScale, SeedBlackHoleMass_Msun, SofteningBndry, &
          SofteningBndryMaxPhys, SofteningBulge, SofteningBulgeMaxPhys, &
          SofteningDisk, SofteningDiskMaxPhys, SofteningGas, &
          SofteningGasMaxPhys, SofteningHalo, SofteningHaloMaxPhys, &
          SofteningStars, SofteningStarsMaxPhys, StellarEvolutionCut_Gyr, &
          SulphurOverSilicon, TimeBegin, TimeBetGridOutput, &
          TimeBetLineOfSight, TimeBetOnTheFlyFoF, TimeBetSmallSnapshot, &
          TimeBetSnapshot, TimeBetStatistics, TimeLimitCPU, TimeMax, &
          TimeOfFirstGridOutput, TimeOfFirstLineOfSight, &
          TimeOfFirstSmallSnapshot, TimeOfFirstSnapshot, &
          TreeDomainUpdateFrequency, UnitLength_in_cm, UnitMass_in_g, &
          UnitVelocity_in_cm_per_s, massDMpart
     character(len=1, kind=c_char), dimension(256) :: BH_feedback_mode, &
          CoolTablePath, CpuFile, EnergyFile, ExtraOutputListFilename, &
          IMF_LifetimeModel, IMF_Model, InfoFile, InitCondFile, OutputDir, &
          OutputListFilename, RestartFile, ResubmitCommand, RunLabel, &
          SNIa_Model, SmallSnapshotFileBase, SnapshotFileBase, TimebinFile, &
          TimingsFile, YieldTablePath, stellar_feedback_DeltaT, &
          stellar_feedback_mode, stellar_feedback_tvir
  end type eagle_runtime_pars_t

  type, bind(C) :: eagle_chemical_elements_t
     integer(c_int) :: BG_NELEMENTS
     real(c_double) :: CalciumOverSilicon, InitAbundance_Carbon, &
          InitAbundance_Helium, InitAbundance_Hydrogen, InitAbundance_Iron, &
          InitAbundance_Magnesium, InitAbundance_Neon, InitAbundance_Nitrogen, &
          InitAbundance_Oxygen, InitAbundance_Silicon, SolarAbundance, &
          SolarAbundance_Calcium, SolarAbundance_Carbon, &
          SolarAbundance_Helium, SolarAbundance_Hydrogen, &
          SolarAbundance_Iron, SolarAbundance_Magnesium, SolarAbundance_Neon, &
          SolarAbundance_Nitrogen, SolarAbundance_Oxygen, &
          SolarAbundance_Silicon, SolarAbundance_Sulphur, SulphurOverSilicon
     character(len=1, kind=c_char), dimension(21,9) :: ElementNames
  end type eagle_chemical_elements_t

  type, bind(C) :: eagle_parameters_t
     type(eagle_chemical_elements_t) :: chemical_elements
  end type eagle_parameters_t

  type, bind(C) :: eagle_config_t
     character(len=1, kind=c_char), dimension(256) :: Config_option_000, &
          Config_option_001, Config_option_002, Config_option_003, &
          Config_option_004, Config_option_005, Config_option_006, &
          Config_option_007, Config_option_008, Config_option_009, &
          Config_option_010, Config_option_011, Config_option_012, &
          Config_option_013, Config_option_014, Config_option_015, &
          Config_option_016, Config_option_017, Config_option_018, &
          Config_option_019, Config_option_020, Config_option_021, &
          Config_option_022, Config_option_023, Config_option_024, &
          Config_option_025, Config_option_026, Config_option_027, &
          Config_option_028, Config_option_029, Config_option_030, &
          Config_option_031, Config_option_032, Config_option_033, &
          Config_option_034, Config_option_035, Config_option_036, &
          Config_option_037, Config_option_038, Config_option_039, &
          Config_option_040, Config_option_041, Config_option_042, &
          Config_option_043, Config_option_044, Config_option_045, &
          Config_option_046, Config_option_047, Config_option_048, &
          Config_option_049, Config_option_050, Config_option_051, &
          Config_option_052, Config_option_053, Config_option_054, &
          Config_option_055, Config_option_056, Config_option_057, &
          Config_option_058, Config_option_059, SVN_Version
  end type eagle_config_t


  type, bind(C) :: eagle_t
     type(eagle_header_t) :: header
     type(eagle_units_t) :: units
     type(eagle_constants_t) :: constants
     type(eagle_runtime_pars_t) :: runtime_pars
     type(eagle_parameters_t) :: parameters
     type(eagle_config_t) :: config
  end type eagle_t


  type, bind(C) :: eagle_dset_info_t
     real(c_float) :: aexp_scale_exponent, h_scale_exponent;
     real(c_double) :: CGSConversionFactor
     character(len=1, kind=c_char), dimension(256) :: VarDescription
  end type eagle_dset_info_t

end module eagle_types
