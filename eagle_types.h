#ifndef _EAGLE_TYPES_H_
#define _EAGLE_TYPES_H_


#ifdef __cplusplus
#define extern "C" {
#endif


#ifndef _STRING_LEN_
#define _STRING_LEN_ 256
#endif


/* Particle types */
enum _PTypes
  {
    gas_particles = 0,
    DM_particles = 1,
    star_particles = 4,
    BH_particles = 5,
  } PType;


typedef struct _eagle_header_t
{
  double BoxSize, E_z, ExpansionFactor, H_z, HubbleParam, Omega0,
    OmegaBaryon, OmegaLambda, Redshift, Time, MassTable[6];
  int Flag_Cooling, Flag_DoublePrecision, Flag_Feedback, Flag_IC_Info,
    Flag_Metals, Flag_Sfr, Flag_StellarAge, NumFilesPerSnapshot,
    NumPart_ThisFile[6], NumPart_Total[6], NumPart_Total_HighWord[6];
  char RunLabel[_STRING_LEN_];
} eagle_header_t;


typedef struct _eagle_units_t
{
  double UnitDensity_in_cgs, UnitEnergy_in_cgs, UnitLength_in_cm,
    UnitMass_in_g, UnitPressure_in_cgs, UnitTime_in_s, UnitVelocity_in_cm_per_s;
} eagle_units_t;


typedef struct _eagle_constatns_t
{
  double AVOGADRO, BOLTZMANN, C, CM_PER_MPC, ELECTRONCHARGE, ELECTRONMASS,
    EV_TO_ERG, GAMMA, GAS_CONST, GRAVITY, HUBBLE, PI, PLANCK, PROTONMASS,
    RAD_CONST, SEC_PER_MEGAYEAR, SEC_PER_YEAR, SOLAR_LUM, SOLAR_MASS,
    STEFAN, THOMPSON, T_CMB0, Z_Solar;
} eagle_constants_t;


typedef struct _eagle_runtime_pars_t
{
  int AGB_EnergyTransferOn, AGB_MassTransferOn, ComovingIntegrationOn,
    CoolingOn, DesLinkNgb, DesNumNgb, FoFFormat, FoFOutputListOn, Generations,
    ICFormat, MaxMemSize, MetDepCoolingOn, NumFilesPerSnapshot,
    NumFilesWrittenInParallel, OutputListOn, PeriodicBoundariesOn, ResubmitOn,
    SF_THRESH_MaxPhysDensOn, SNII_EnergyTransferOn, SNII_MassTransferOn,
    SNII_WindIsotropicOn, SNIa_EnergyTransferOn,
    SNIa_EnergyTransferStochastic, SNIa_MassTransferOn, SmallOutputListOn,
    SmallOutputTar, SnapFormat, StarformationOn, StellarEnergyFeedbackOn,
    StellarEvol_FeedbackOn, StellarEvolutionTimestepInterval,
    StellarMetalFeedbackOn, TypeOfOpeningCriterion, TypeOfTimestepCriterion;
  float ArtBulkViscConst, ArtBulkViscConstMin, ArtDiffConst, ArtDiffConstMin,
    BHAllocFactor, BH_ConstantHeatTemp, BH_MaxHeatLimit, BH_MaxHeatTemp,
    BH_MaxMergingDistanceFactor, BH_MaxRepositionDistanceFactor,
    BH_MinHeatLimit, BH_MinHeatTemp, BH_maxHeatingProbability,
    BlackHoleAccretionFactor, BlackHoleAccretionSlope,
    BlackHoleEddingtonFactor, BlackHoleFeedbackFactor,
    BlackHoleMaxAccretionRadius, BlackHoleNgbFactor,
    BlackHoleNumberOfNeighboursToHeat, BlackHoleRadiativeEfficiency,
    BlackHoleViscousAlpha, BoxSize, BufferSize, CalciumOverSilicon, CourantFac,
    CpuTimeBetRestartFile, DesNumNgbStar, DesNumNgbYoungStar,
    EOS_Cool_GammaEffective, EOS_Cool_MinOverDens, EOS_Cool_MinPhysDens_HpCM3,
    EOS_Cool_TempNorm_K, EOS_Jeans_GammaEffective, EOS_Jeans_MinOverDens,
    EOS_Jeans_MinPhysDens_HpCM3, EOS_Jeans_TempNorm_K, EOS_NormPhysDens_HpCM3,
    ErrTolForceAcc, ErrTolIntAccuracy, ErrTolTheta, ErrTolThetaSubfind,
    GravityConstantInternal, HubbleParam, IMF_Exponent, IMF_MaxMass_MSUN,
    IMF_MinMass_MSUN, InitAbundance_Carbon, InitAbundance_Helium,
    InitAbundance_Hydrogen, InitAbundance_Iron, InitAbundance_Magnesium,
    InitAbundance_Neon, InitAbundance_Nitrogen, InitAbundance_Oxygen,
    InitAbundance_Silicon, InitGasTemp, InitMetallicity, MaxNumNgbDeviation,
    MaxRMSDisplacementFac, MaxSizeTimestep, MaxSmoothingLengthChange,
    MetAllocFactor, MinFoFMassForNewSeed_Msun, MinGasHsmlFractional,
    MinGasTemp, MinSizeTimestep, Omega0, OmegaBaryon, OmegaLambda,
    PartAllocFactor, REION_H_Heating_EVpH, REION_H_ZCenter,
    REION_He_Heating_EVpH, REION_He_ZCenter, REION_He_ZSigma,
    SF_SchmidtLawCoeff_MSUNpYRpKPC2, SF_SchmidtLawExponent,
    SF_SchmidtLawHighDensExponent, SF_SchmidtLawHighDensThresh_HpCM3,
    SF_THRESH_MaxPhysDens_HpCM3, SF_THRESH_MetDepSFThreshMaxThresh_HpCM3,
    SF_THRESH_MetDepSFThreshNorm_HpCM3, SF_THRESH_MetDepSFThreshSlope,
    SF_THRESH_MinOverDens, SF_THRESH_MinPhysDens_HpCM3,
    SF_THRESH_TempMargin_DEX, SNII_Delta_T_Divided_By_T_Vir, SNII_Delta_T_K,
    SNII_Energy_ERG, SNII_Factor_Carbon, SNII_Factor_Helium,
    SNII_Factor_Hydrogen, SNII_Factor_Iron, SNII_Factor_Magnesium,
    SNII_Factor_Neon, SNII_Factor_Nitrogen, SNII_Factor_Oxygen,
    SNII_Factor_Silicon, SNII_MaxEnergyFraction, SNII_MaxMass_MSUN,
    SNII_Max_Delta_T_K, SNII_MinEnergyFraction, SNII_MinMass_MSUN,
    SNII_Min_Delta_T_K, SNII_Tvir0_K, SNII_Width_logTvir_dex,
    SNII_WindDelay_YR, SNII_exponent_Delta_T, SNII_normalisation_Delta_T_K,
    SNII_rhogas_physdensnormfac, SNII_rhogas_power, SNII_zdep_power,
    SNIa_Efficiency, SNIa_EjectaVelocity_KMpS, SNIa_EnergyFraction,
    SNIa_Energy_ERG, SNIa_TimeScale, SeedBlackHoleMass_Msun,
    SofteningBndry, SofteningBndryMaxPhys, SofteningBulge,
    SofteningBulgeMaxPhys, SofteningDisk, SofteningDiskMaxPhys, SofteningGas,
    SofteningGasMaxPhys, SofteningHalo, SofteningHaloMaxPhys, SofteningStars,
    SofteningStarsMaxPhys, StellarEvolutionCut_Gyr, SulphurOverSilicon,
    TimeBegin, TimeBetGridOutput, TimeBetLineOfSight, TimeBetOnTheFlyFoF,
    TimeBetSmallSnapshot, TimeBetSnapshot, TimeBetStatistics, TimeLimitCPU,
    TimeMax, TimeOfFirstGridOutput, TimeOfFirstLineOfSight,
    TimeOfFirstSmallSnapshot, TimeOfFirstSnapshot, TreeDomainUpdateFrequency,
    UnitLength_in_cm, UnitMass_in_g, UnitVelocity_in_cm_per_s, massDMpart;
  char BH_feedback_mode[_STRING_LEN_], CoolTablePath[_STRING_LEN_],
    CpuFile[_STRING_LEN_], EnergyFile[_STRING_LEN_],
    ExtraOutputListFilename[_STRING_LEN_], IMF_LifetimeModel[_STRING_LEN_],
    IMF_Model[_STRING_LEN_], InfoFile[_STRING_LEN_],
    InitCondFile[_STRING_LEN_], OutputDir[_STRING_LEN_],
    OutputListFilename[_STRING_LEN_], RestartFile[_STRING_LEN_],
    ResubmitCommand[_STRING_LEN_], RunLabel[_STRING_LEN_],
    SNIa_Model[_STRING_LEN_], SmallSnapshotFileBase[_STRING_LEN_],
    SnapshotFileBase[_STRING_LEN_], TimebinFile[_STRING_LEN_],
    TimingsFile[_STRING_LEN_], YieldTablePath[_STRING_LEN_],
    stellar_feedback_DeltaT[_STRING_LEN_], stellar_feedback_mode[_STRING_LEN_],
    stellar_feedback_tvir[_STRING_LEN_];
} eagle_runtime_pars_t;


typedef struct _eagle_chemical_elements_t
{
  int BG_NELEMENTS;
  double CalciumOverSilicon, InitAbundance_Carbon, InitAbundance_Helium,
    InitAbundance_Hydrogen, InitAbundance_Iron, InitAbundance_Magnesium,
    InitAbundance_Neon, InitAbundance_Nitrogen, InitAbundance_Oxygen,
    InitAbundance_Silicon, SolarAbundance, SolarAbundance_Calcium,
    SolarAbundance_Carbon, SolarAbundance_Helium, SolarAbundance_Hydrogen,
    SolarAbundance_Iron, SolarAbundance_Magnesium, SolarAbundance_Neon,
    SolarAbundance_Nitrogen, SolarAbundance_Oxygen, SolarAbundance_Silicon,
    SolarAbundance_Sulphur, SulphurOverSilicon;
  char ElementNames[9][21];
} eagle_chemical_elements_t;


typedef struct _eagle_parameters_t
{
  eagle_chemical_elements_t chemical_elements;
} eagle_parameters_t;


typedef struct _eagle_config_t
{
  char Config_option_000[_STRING_LEN_], Config_option_001[_STRING_LEN_],
    Config_option_002[_STRING_LEN_], Config_option_003[_STRING_LEN_],
    Config_option_004[_STRING_LEN_], Config_option_005[_STRING_LEN_],
    Config_option_006[_STRING_LEN_], Config_option_007[_STRING_LEN_],
    Config_option_008[_STRING_LEN_], Config_option_009[_STRING_LEN_],
    Config_option_010[_STRING_LEN_], Config_option_011[_STRING_LEN_],
    Config_option_012[_STRING_LEN_], Config_option_013[_STRING_LEN_],
    Config_option_014[_STRING_LEN_], Config_option_015[_STRING_LEN_],
    Config_option_016[_STRING_LEN_], Config_option_017[_STRING_LEN_],
    Config_option_018[_STRING_LEN_], Config_option_019[_STRING_LEN_],
    Config_option_020[_STRING_LEN_], Config_option_021[_STRING_LEN_],
    Config_option_022[_STRING_LEN_], Config_option_023[_STRING_LEN_],
    Config_option_024[_STRING_LEN_], Config_option_025[_STRING_LEN_],
    Config_option_026[_STRING_LEN_], Config_option_027[_STRING_LEN_],
    Config_option_028[_STRING_LEN_], Config_option_029[_STRING_LEN_],
    Config_option_030[_STRING_LEN_], Config_option_031[_STRING_LEN_],
    Config_option_032[_STRING_LEN_], Config_option_033[_STRING_LEN_],
    Config_option_034[_STRING_LEN_], Config_option_035[_STRING_LEN_],
    Config_option_036[_STRING_LEN_], Config_option_037[_STRING_LEN_],
    Config_option_038[_STRING_LEN_], Config_option_039[_STRING_LEN_],
    Config_option_040[_STRING_LEN_], Config_option_041[_STRING_LEN_],
    Config_option_042[_STRING_LEN_], Config_option_043[_STRING_LEN_],
    Config_option_044[_STRING_LEN_], Config_option_045[_STRING_LEN_],
    Config_option_046[_STRING_LEN_], Config_option_047[_STRING_LEN_],
    Config_option_048[_STRING_LEN_], Config_option_049[_STRING_LEN_],
    Config_option_050[_STRING_LEN_], Config_option_051[_STRING_LEN_],
    Config_option_052[_STRING_LEN_], Config_option_053[_STRING_LEN_],
    Config_option_054[_STRING_LEN_], Config_option_055[_STRING_LEN_],
    Config_option_056[_STRING_LEN_], Config_option_057[_STRING_LEN_],
    Config_option_058[_STRING_LEN_], Config_option_059[_STRING_LEN_],
    SVN_Version[_STRING_LEN_];
} eagle_config_t;


typedef struct _eagle_t
{
  eagle_header_t header;
  eagle_units_t units;
  eagle_constants_t constants;
  eagle_runtime_pars_t runtime_pars;
  eagle_parameters_t parameters;
  eagle_config_t config;
} eagle_t;


typedef struct _eagle_dset_info_t
{
  float aexp_scale_exponent;
  float h_scale_exponent;
  double CGSConversionFactor;
  char VarDescription[_STRING_LEN_];
} eagle_dset_info_t;


typedef struct _eagle_hashtable_t
{
  int *FirstKeyInFile;
  int *LastKeyInFile;
  int *NumKeysInFile;
  int **NumParticleInCell;
} eagle_hashtable_t;


typedef struct _eagle_hash_t
{
  int *map;
  int map_len, bits, num_files;
  double box_size;
  eagle_hashtable_t table[6];
} eagle_hash_t;


#ifdef __cplusplus
#define }
#endif


#endif /* _EAGLE_TYPES_H_ */
