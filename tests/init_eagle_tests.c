/*
 * init_eagle_tests.c
 */


#include <cgreen/cgreen.h>
#include <math.h>
#include "./../src/init_eagle.h"


#define EAGLE_PATH "./snapshot/eagle_snap.%d.hdf5"


Describe(init_eagle);
BeforeEach(init_eagle) {};
AfterEach(init_eagle) {};


Ensure(init_eagle, fills_eagle_object)
{
  eagle_t eagle;

  int err = init_eagle(EAGLE_PATH, &eagle);
  assert_that(err, is_not_equal_to(EXIT_FAILURE));
  assert_that(err, is_equal_to(EXIT_SUCCESS));

  /* Header */
  assert_that_double(eagle.header.BoxSize, is_equal_to_double(8.47125));
  assert_that_double(eagle.header.E_z, is_equal_to_double(4.537093477630583));
  assert_that_double(eagle.header.ExpansionFactor, is_equal_to_double(0.2489726990748467));
  assert_that(eagle.header.Flag_Cooling, is_equal_to(0));
  assert_that(eagle.header.Flag_DoublePrecision, is_equal_to(0));
  assert_that(eagle.header.Flag_Feedback, is_equal_to(0));
  assert_that(eagle.header.Flag_IC_Info, is_equal_to(3));
  assert_that(eagle.header.Flag_Metals, is_equal_to(0));
  assert_that(eagle.header.Flag_Sfr, is_equal_to(0));
  assert_that(eagle.header.Flag_StellarAge, is_equal_to(0));
  assert_that_double(eagle.header.H_z, is_equal_to_double(9.964708881888158E-18));
  assert_that_double(eagle.header.HubbleParam, is_equal_to_double(0.6777));
  assert_that_double(eagle.header.MassTable[0], is_equal_to_double(0.0));
  assert_that_double(eagle.header.MassTable[1], is_equal_to_double(6.570332889156362E-4));
  assert_that_double(eagle.header.MassTable[2], is_equal_to_double(0.0));
  assert_that_double(eagle.header.MassTable[3], is_equal_to_double(0.0));
  assert_that_double(eagle.header.MassTable[4], is_equal_to_double(0.0));
  assert_that_double(eagle.header.MassTable[5], is_equal_to_double(0.0));
  assert_that(eagle.header.NumFilesPerSnapshot, is_equal_to(16));
  assert_that(eagle.header.NumPart_ThisFile[0], is_equal_to(413769));
  assert_that(eagle.header.NumPart_ThisFile[1], is_equal_to(408155));
  assert_that(eagle.header.NumPart_ThisFile[2], is_equal_to(0));
  assert_that(eagle.header.NumPart_ThisFile[3], is_equal_to(0));
  assert_that(eagle.header.NumPart_ThisFile[4], is_equal_to(1197));
  assert_that(eagle.header.NumPart_ThisFile[5], is_equal_to(14));
  assert_that(eagle.header.NumPart_Total[0], is_equal_to(6617306));
  assert_that(eagle.header.NumPart_Total[1], is_equal_to(6644672));
  assert_that(eagle.header.NumPart_Total[2], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total[3], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total[4], is_equal_to(27116));
  assert_that(eagle.header.NumPart_Total[5], is_equal_to(247));
  assert_that(eagle.header.NumPart_Total_HighWord[0], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total_HighWord[1], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total_HighWord[2], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total_HighWord[3], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total_HighWord[4], is_equal_to(0));
  assert_that(eagle.header.NumPart_Total_HighWord[5], is_equal_to(0));
  assert_that_double(eagle.header.Omega0, is_equal_to_double(0.307));
  assert_that_double(eagle.header.OmegaBaryon, is_equal_to_double(0.0482519));
  assert_that_double(eagle.header.OmegaLambda, is_equal_to_double(0.693));
  assert_that_double(eagle.header.Redshift, is_equal_to_double(3.0165046357126));
  assert_that(eagle.header.RunLabel, is_equal_to_string("\"Eagle"));
  assert_that_double(eagle.header.Time, is_equal_to_double(0.2489726990748467));

  /* Units */
  assert_that_double(eagle.units.UnitDensity_in_cgs, is_equal_to_double(6.769911178294543E-31));
  assert_that_double(eagle.units.UnitEnergy_in_cgs, is_equal_to_double(1.989E53));
  assert_that_double(eagle.units.UnitLength_in_cm, is_equal_to_double(3.085678E24));
  assert_that_double(eagle.units.UnitMass_in_g, is_equal_to_double(1.989E43));
  assert_that_double(eagle.units.UnitPressure_in_cgs, is_equal_to_double(6.769911178294542E-21));
  assert_that_double(eagle.units.UnitTime_in_s, is_equal_to_double(3.085678E19));
  assert_that_double(eagle.units.UnitVelocity_in_cm_per_s, is_equal_to_double(100000.0));

  /* Constants */
  assert_that_double(eagle.constants.AVOGADRO, is_equal_to_double(6.0222E23));
  assert_that_double(eagle.constants.BOLTZMANN, is_equal_to_double(1.38066E-16));
  assert_that_double(eagle.constants.C, is_equal_to_double(2.9979E10));
  assert_that_double(eagle.constants.CM_PER_MPC, is_equal_to_double(3.085678E24));
  assert_that_double(eagle.constants.ELECTRONCHARGE, is_equal_to_double(4.8032E-10));
  assert_that_double(eagle.constants.ELECTRONMASS, is_equal_to_double(9.10953E-28));
  assert_that_double(eagle.constants.EV_TO_ERG, is_equal_to_double(1.60217646E-12));
  assert_that_double(eagle.constants.GAMMA, is_equal_to_double(1.6666666666666667));
  assert_that_double(eagle.constants.GAS_CONST, is_equal_to_double(8.31425E7));
  assert_that_double(eagle.constants.GRAVITY, is_equal_to_double(6.672E-8));
  assert_that_double(eagle.constants.HUBBLE, is_equal_to_double(3.2407789E-18));
  assert_that_double(eagle.constants.PI, is_equal_to_double(3.1415927));
  assert_that_double(eagle.constants.PLANCK, is_equal_to_double(6.6262E-27));
  assert_that_double(eagle.constants.PROTONMASS, is_equal_to_double(1.6726E-24));
  assert_that_double(eagle.constants.RAD_CONST, is_equal_to_double(7.565E-15));
  assert_that_double(eagle.constants.SEC_PER_MEGAYEAR, is_equal_to_double(3.155E13));
  assert_that_double(eagle.constants.SEC_PER_YEAR, is_equal_to_double(3.155E7));
  assert_that_double(eagle.constants.SOLAR_LUM, is_equal_to_double(3.826E33));
  assert_that_double(eagle.constants.SOLAR_MASS, is_equal_to_double(1.989E33));
  assert_that_double(eagle.constants.STEFAN, is_equal_to_double(7.5657E-15));
  assert_that_double(eagle.constants.THOMPSON, is_equal_to_double(6.65245E-25));
  assert_that_double(eagle.constants.T_CMB0, is_equal_to_double(2.728));
  assert_that_double(eagle.constants.Z_Solar, is_equal_to_double(0.012663729));

  /* Parameters/ChemicalElements */
  assert_that(eagle.parameters.chemical_elements.BG_NELEMENTS, is_equal_to(9));
  assert_that_double(eagle.parameters.chemical_elements.CalciumOverSilicon, is_equal_to_double(0.0941736));
  assert_that(eagle.parameters.chemical_elements.ElementNames[0], is_equal_to_string("Hydrogen"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[1], is_equal_to_string("Helium"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[2], is_equal_to_string("Carbon"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[3], is_equal_to_string("Nitrogen"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[4], is_equal_to_string("Oxygen"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[5], is_equal_to_string("Neon"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[6], is_equal_to_string("Magnesium"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[7], is_equal_to_string("Silicon"));
  assert_that(eagle.parameters.chemical_elements.ElementNames[8], is_equal_to_string("Iron"));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Carbon, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Helium, is_equal_to_double(0.248));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Hydrogen, is_equal_to_double(0.752));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Iron, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Magnesium, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Neon, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Nitrogen, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Oxygen, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.InitAbundance_Silicon, is_equal_to_double(0.0));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance, is_equal_to_double(0.01294681429862976));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Calcium, is_equal_to_double(6.435500108636916E-5));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Carbon, is_equal_to_double(0.002066543558612466));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Helium, is_equal_to_double(0.2805553376674652));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Hydrogen, is_equal_to_double(0.706497848033905));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Iron, is_equal_to_double(0.0011032151523977518));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Magnesium, is_equal_to_double(5.907064187340438E-4));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Neon, is_equal_to_double(0.0014144604792818427));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Nitrogen, is_equal_to_double(8.356256294064224E-4));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Oxygen, is_equal_to_double(0.00549262436106801));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Silicon, is_equal_to_double(6.825873861089349E-4));
  assert_that_double(eagle.parameters.chemical_elements.SolarAbundance_Sulphur, is_equal_to_double(4.0898521547205746E-4));
  assert_that_double(eagle.parameters.chemical_elements.SulphurOverSilicon, is_equal_to_double(0.605416));

  /* Runtime Pars */
  assert_that(eagle.runtime_pars.AGB_EnergyTransferOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.AGB_MassTransferOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.ArtBulkViscConst, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.ArtBulkViscConstMin, is_equal_to_double(0.05));
  assert_that_double(eagle.runtime_pars.ArtDiffConst, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.ArtDiffConstMin, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.BHAllocFactor, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.BH_ConstantHeatTemp, is_equal_to_double(3.16228E8));
  assert_that_double(eagle.runtime_pars.BH_MaxHeatLimit, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.BH_MaxHeatTemp, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.BH_MaxMergingDistanceFactor, is_equal_to_double(3.0));
  assert_that_double(eagle.runtime_pars.BH_MaxRepositionDistanceFactor, is_equal_to_double(3.0));
  assert_that_double(eagle.runtime_pars.BH_MinHeatLimit, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.BH_MinHeatTemp, is_equal_to_double(0.0));
  assert_that(eagle.runtime_pars.BH_feedback_mode, is_equal_to_string("constant"));
  assert_that_double(eagle.runtime_pars.BH_maxHeatingProbability, is_equal_to_double(0.3));
  assert_that_double(eagle.runtime_pars.BlackHoleAccretionFactor, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.BlackHoleAccretionSlope, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.BlackHoleEddingtonFactor, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.BlackHoleFeedbackFactor, is_equal_to_double(0.15));
  assert_that_double(eagle.runtime_pars.BlackHoleMaxAccretionRadius, is_equal_to_double(1.0E10));
  assert_that_double(eagle.runtime_pars.BlackHoleNgbFactor, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.BlackHoleNumberOfNeighboursToHeat, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.BlackHoleRadiativeEfficiency, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.BlackHoleViscousAlpha, is_equal_to_double(1000000.0));
  assert_that_double(eagle.runtime_pars.BoxSize, is_greater_than_double(8.47124));
  assert_that_double(eagle.runtime_pars.BoxSize, is_less_than_double(8.47126));
  assert_that_double(eagle.runtime_pars.BufferSize, is_equal_to_double(150.0));
  assert_that_double(eagle.runtime_pars.CalciumOverSilicon, is_equal_to_double(0.0941736));
  assert_that_double(eagle.runtime_pars.ComovingIntegrationOn, is_equal_to_double(1));
  assert_that(eagle.runtime_pars.CoolTablePath, is_equal_to_string("/ccc/scratch/cont005/ra1242/crainr/BG_Tables/CoolingTables/"));
  assert_that(eagle.runtime_pars.CoolingOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.CourantFac, is_equal_to_double(0.15));
  assert_that(eagle.runtime_pars.CpuFile, is_equal_to_string("cpu.txt"));
  assert_that_double(eagle.runtime_pars.CpuTimeBetRestartFile, is_equal_to_double(3600.0));
  assert_that(eagle.runtime_pars.DesLinkNgb, is_equal_to(20));
  assert_that(eagle.runtime_pars.DesNumNgb, is_equal_to(58));
  assert_that_double(eagle.runtime_pars.DesNumNgbStar, is_equal_to_double(48.0));
  assert_that_double(eagle.runtime_pars.DesNumNgbYoungStar, is_equal_to_double(48.0));
  assert_that_double(eagle.runtime_pars.EOS_Cool_GammaEffective, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.EOS_Cool_MinOverDens, is_equal_to_double(10.0));
  assert_that_double(eagle.runtime_pars.EOS_Cool_MinPhysDens_HpCM3, is_equal_to_double(1.0E-5));
  assert_that_double(eagle.runtime_pars.EOS_Cool_TempNorm_K, is_equal_to_double(8000.0));
  assert_that_double(eagle.runtime_pars.EOS_Jeans_GammaEffective, is_equal_to_double(1.3333334));
  assert_that_double(eagle.runtime_pars.EOS_Jeans_MinOverDens, is_equal_to_double(10.0));
  assert_that_double(eagle.runtime_pars.EOS_Jeans_MinPhysDens_HpCM3, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.EOS_Jeans_TempNorm_K, is_equal_to_double(8000.0));
  assert_that_double(eagle.runtime_pars.EOS_NormPhysDens_HpCM3, is_equal_to_double(0.1));
  assert_that(eagle.runtime_pars.EnergyFile, is_equal_to_string("energy.txt"));
  assert_that_double(eagle.runtime_pars.ErrTolForceAcc, is_equal_to_double(0.005));
  assert_that_double(eagle.runtime_pars.ErrTolIntAccuracy, is_equal_to_double(0.025));
  assert_that_double(eagle.runtime_pars.ErrTolTheta, is_equal_to_double(0.6));
  assert_that_double(eagle.runtime_pars.ErrTolThetaSubfind, is_equal_to_double(0.6));
  assert_that(eagle.runtime_pars.ExtraOutputListFilename, is_equal_to_string("/ccc/scratch/cont005/ra1242/crainr/OutputLists/eagle_snip_400_z20p00_z00p00.txt"));
  assert_that(eagle.runtime_pars.FoFFormat, is_equal_to(3));
  assert_that(eagle.runtime_pars.FoFOutputListOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.Generations, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.GravityConstantInternal, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.HubbleParam, is_equal_to_double(0.6777));
  assert_that(eagle.runtime_pars.ICFormat, is_equal_to(3));
  assert_that_double(eagle.runtime_pars.IMF_Exponent, is_equal_to_double(0.0));
  assert_that(eagle.runtime_pars.IMF_LifetimeModel, is_equal_to_string("P98"));
  assert_that_double(eagle.runtime_pars.IMF_MaxMass_MSUN, is_equal_to_double(100.0));
  assert_that_double(eagle.runtime_pars.IMF_MinMass_MSUN, is_equal_to_double(0.1));
  assert_that(eagle.runtime_pars.IMF_Model, is_equal_to_string("Chabrier"));
  assert_that(eagle.runtime_pars.InfoFile, is_equal_to_string("info.txt"));
  assert_that_double(eagle.runtime_pars.InitAbundance_Carbon, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Helium, is_equal_to_double(0.248));
  assert_that_double(eagle.runtime_pars.InitAbundance_Hydrogen, is_equal_to_double(0.752));
  assert_that_double(eagle.runtime_pars.InitAbundance_Iron, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Magnesium, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Neon, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Nitrogen, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Oxygen, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.InitAbundance_Silicon, is_equal_to_double(0.0));
  assert_that(eagle.runtime_pars.InitCondFile, is_equal_to_string("./ic_dir/snapdir_000/snap_000"));
  assert_that_double(eagle.runtime_pars.InitGasTemp, is_equal_to_double(268.700012));
  assert_that_double(eagle.runtime_pars.InitMetallicity, is_equal_to_double(0.0));
  assert_that(eagle.runtime_pars.MaxMemSize, is_equal_to(3800));
  assert_that_double(eagle.runtime_pars.MaxNumNgbDeviation, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.MaxRMSDisplacementFac, is_equal_to_double(0.25));
  assert_that_double(eagle.runtime_pars.MaxSizeTimestep, is_equal_to_double(0.01));
  assert_that_double(eagle.runtime_pars.MaxSmoothingLengthChange, is_equal_to_double(1.26));
  assert_that_double(eagle.runtime_pars.MetAllocFactor, is_equal_to_double(0.4));
  assert_that(eagle.runtime_pars.MetDepCoolingOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.MinFoFMassForNewSeed_Msun, is_equal_to_double(1.0E10));
  assert_that_double(eagle.runtime_pars.MinGasHsmlFractional, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.MinGasTemp, is_equal_to_double(100.0));
  assert_that_double(eagle.runtime_pars.MinSizeTimestep, is_equal_to_double(6.0E-8));
  assert_that(eagle.runtime_pars.NumFilesPerSnapshot, is_equal_to(16));
  assert_that(eagle.runtime_pars.NumFilesWrittenInParallel, is_equal_to(16));
  assert_that_double(eagle.runtime_pars.Omega0, is_equal_to_double(0.307));
  assert_that_double(eagle.runtime_pars.OmegaBaryon, is_equal_to_double(0.0482519));
  assert_that_double(eagle.runtime_pars.OmegaLambda, is_equal_to_double(0.693));
  assert_that(eagle.runtime_pars.OutputDir, is_equal_to_string("data"));
  assert_that(eagle.runtime_pars.OutputListFilename, is_equal_to_string("/ccc/scratch/cont005/ra1242/crainr/OutputLists/eagle_outputs_new.txt"));
  assert_that(eagle.runtime_pars.OutputListOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.PartAllocFactor, is_equal_to_double(3.5));
  assert_that(eagle.runtime_pars.PeriodicBoundariesOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.REION_H_Heating_EVpH, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.REION_H_ZCenter, is_equal_to_double(11.5));
  assert_that_double(eagle.runtime_pars.REION_He_Heating_EVpH, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.REION_He_ZCenter, is_equal_to_double(3.5));
  assert_that_double(eagle.runtime_pars.REION_He_ZSigma, is_equal_to_double(0.5));
  assert_that(eagle.runtime_pars.RestartFile, is_equal_to_string("restart"));
  assert_that(eagle.runtime_pars.ResubmitCommand, is_equal_to_string("./autoresubmit.sh"));
  assert_that(eagle.runtime_pars.ResubmitOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.RunLabel, is_equal_to_string("\"Eagle"));
  assert_that_double(eagle.runtime_pars.SF_SchmidtLawCoeff_MSUNpYRpKPC2, is_equal_to_double(1.515E-4));
  assert_that_double(eagle.runtime_pars.SF_SchmidtLawExponent, is_equal_to_double(1.4));
  assert_that_double(eagle.runtime_pars.SF_SchmidtLawHighDensExponent, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.SF_SchmidtLawHighDensThresh_HpCM3, is_equal_to_double(1000.0));
  assert_that(eagle.runtime_pars.SF_THRESH_MaxPhysDensOn, is_equal_to(0));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MaxPhysDens_HpCM3, is_equal_to_double(100000.0));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MetDepSFThreshMaxThresh_HpCM3, is_equal_to_double(10.0));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MetDepSFThreshNorm_HpCM3, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MetDepSFThreshSlope, is_equal_to_double(-0.64));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MinOverDens, is_equal_to_double(57.7));
  assert_that_double(eagle.runtime_pars.SF_THRESH_MinPhysDens_HpCM3, is_equal_to_double(0.1));
  assert_that_double(eagle.runtime_pars.SF_THRESH_TempMargin_DEX, is_equal_to_double(0.5));
  assert_that_double(eagle.runtime_pars.SNII_Delta_T_Divided_By_T_Vir, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNII_Delta_T_K, is_equal_to_double(3.16228E7));
  assert_that(eagle.runtime_pars.SNII_EnergyTransferOn, is_equal_to(1));
  /* assert_that_double(eagle.runtime_pars.SNII_Energy_ERG, is_equal_to_double(INFINITY)); */
  assert_that_double(eagle.runtime_pars.SNII_Factor_Carbon, is_equal_to_double(0.5));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Helium, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Hydrogen, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Iron, is_equal_to_double(0.5));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Magnesium, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Neon, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Nitrogen, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Oxygen, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_Factor_Silicon, is_equal_to_double(1.0));
  assert_that(eagle.runtime_pars.SNII_MassTransferOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.SNII_MaxEnergyFraction, is_equal_to_double(3.0));
  assert_that_double(eagle.runtime_pars.SNII_MaxMass_MSUN, is_equal_to_double(100.0));
  assert_that_double(eagle.runtime_pars.SNII_Max_Delta_T_K, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNII_MinEnergyFraction, is_equal_to_double(0.3));
  assert_that_double(eagle.runtime_pars.SNII_MinMass_MSUN, is_equal_to_double(6.0));
  assert_that_double(eagle.runtime_pars.SNII_Min_Delta_T_K, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNII_Tvir0_K, is_equal_to_double(0.0012663729));
  assert_that_double(eagle.runtime_pars.SNII_Width_logTvir_dex, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_WindDelay_YR, is_equal_to_double(3.0E7));
  assert_that(eagle.runtime_pars.SNII_WindIsotropicOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.SNII_exponent_Delta_T, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNII_normalisation_Delta_T_K, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNII_rhogas_physdensnormfac, is_greater_than_double(6.6));
  assert_that_double(eagle.runtime_pars.SNII_rhogas_physdensnormfac, is_less_than_double(6.8));
  assert_that_double(eagle.runtime_pars.SNII_rhogas_power, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.SNII_zdep_power, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SNIa_Efficiency, is_equal_to_double(0.002));
  assert_that_double(eagle.runtime_pars.SNIa_EjectaVelocity_KMpS, is_equal_to_double(10.0));
  assert_that_double(eagle.runtime_pars.SNIa_EnergyFraction, is_equal_to_double(1.0));
  assert_that(eagle.runtime_pars.SNIa_EnergyTransferOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.SNIa_EnergyTransferStochastic, is_equal_to(1));
  /* assert_that_double(eagle.runtime_pars.SNIa_Energy_ERG, is_equal_to_double(INFINITY)); */
  assert_that(eagle.runtime_pars.SNIa_MassTransferOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.SNIa_Model, is_equal_to_string("Efolding"));
  assert_that_double(eagle.runtime_pars.SNIa_TimeScale, is_equal_to_double(2.0));
  assert_that_double(eagle.runtime_pars.SeedBlackHoleMass_Msun, is_equal_to_double(100000.0));
  assert_that(eagle.runtime_pars.SmallOutputListOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.SmallOutputTar, is_equal_to(1));
  assert_that(eagle.runtime_pars.SmallSnapshotFileBase, is_equal_to_string("snip"));
  assert_that(eagle.runtime_pars.SnapFormat, is_equal_to(3));
  assert_that(eagle.runtime_pars.SnapshotFileBase, is_equal_to_string("snap"));
  assert_that_double(eagle.runtime_pars.SofteningBndry, is_equal_to_double(0.00180239));
  assert_that_double(eagle.runtime_pars.SofteningBndryMaxPhys, is_equal_to_double(4.7439E-4));
  assert_that_double(eagle.runtime_pars.SofteningBulge, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SofteningBulgeMaxPhys, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SofteningDisk, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SofteningDiskMaxPhys, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.SofteningGas, is_equal_to_double(0.00180239));
  assert_that_double(eagle.runtime_pars.SofteningGasMaxPhys, is_equal_to_double(4.7439E-4));
  assert_that_double(eagle.runtime_pars.SofteningHalo, is_equal_to_double(0.00180239));
  assert_that_double(eagle.runtime_pars.SofteningHaloMaxPhys, is_equal_to_double(4.7439E-4));
  assert_that_double(eagle.runtime_pars.SofteningStars, is_equal_to_double(0.00180239));
  assert_that_double(eagle.runtime_pars.SofteningStarsMaxPhys, is_equal_to_double(4.7439E-4));
  assert_that(eagle.runtime_pars.StarformationOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.StellarEnergyFeedbackOn, is_equal_to(1));
  assert_that(eagle.runtime_pars.StellarEvol_FeedbackOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.StellarEvolutionCut_Gyr, is_equal_to_double(0.1));
  assert_that(eagle.runtime_pars.StellarEvolutionTimestepInterval, is_equal_to(10));
  assert_that(eagle.runtime_pars.StellarMetalFeedbackOn, is_equal_to(1));
  assert_that_double(eagle.runtime_pars.SulphurOverSilicon, is_equal_to_double(0.605416));
  assert_that_double(eagle.runtime_pars.TimeBegin, is_equal_to_double(0.0078125));
  assert_that_double(eagle.runtime_pars.TimeBetGridOutput, is_equal_to_double(1.025));
  assert_that_double(eagle.runtime_pars.TimeBetLineOfSight, is_equal_to_double(1.01));
  assert_that_double(eagle.runtime_pars.TimeBetOnTheFlyFoF, is_equal_to_double(1.005));
  assert_that_double(eagle.runtime_pars.TimeBetSmallSnapshot, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.TimeBetSnapshot, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.TimeBetStatistics, is_equal_to_double(0.02));
  assert_that_double(eagle.runtime_pars.TimeLimitCPU, is_equal_to_double(97000.0));
  assert_that_double(eagle.runtime_pars.TimeMax, is_equal_to_double(1.0));
  assert_that_double(eagle.runtime_pars.TimeOfFirstGridOutput, is_equal_to_double(0.05));
  assert_that_double(eagle.runtime_pars.TimeOfFirstLineOfSight, is_equal_to_double(0.09));
  assert_that_double(eagle.runtime_pars.TimeOfFirstSmallSnapshot, is_equal_to_double(0.0));
  assert_that_double(eagle.runtime_pars.TimeOfFirstSnapshot, is_equal_to_double(0.0));
  assert_that(eagle.runtime_pars.TimebinFile, is_equal_to_string("timebins.txt"));
  assert_that(eagle.runtime_pars.TimingsFile, is_equal_to_string("timings.txt"));
  assert_that_double(eagle.runtime_pars.TreeDomainUpdateFrequency, is_equal_to_double(0.005));
  assert_that(eagle.runtime_pars.TypeOfOpeningCriterion, is_equal_to(1));
  assert_that(eagle.runtime_pars.TypeOfTimestepCriterion, is_equal_to(0));
  assert_that_double(eagle.runtime_pars.UnitLength_in_cm, is_equal_to_double(3.085678E24));
  /* assert_that_double(eagle.runtime_pars.UnitMass_in_g, is_equal_to_double(INFINITY)); */
  assert_that_double(eagle.runtime_pars.UnitVelocity_in_cm_per_s, is_equal_to_double(100000.0));
  assert_that(eagle.runtime_pars.YieldTablePath, is_equal_to_string("/ccc/scratch/cont005/ra1242/crainr/BG_Tables/YieldTables/"));
  assert_that_double(eagle.runtime_pars.massDMpart, is_equal_to_double(-1.0));
  assert_that(eagle.runtime_pars.stellar_feedback_DeltaT, is_equal_to_string("constant"));
  assert_that(eagle.runtime_pars.stellar_feedback_mode, is_equal_to_string("thermal"));
  assert_that(eagle.runtime_pars.stellar_feedback_tvir, is_equal_to_string("vel_disp"));

  /* Configs */
  assert_that(eagle.config.Config_option_000, is_equal_to_string("PERIODIC "));
  assert_that(eagle.config.Config_option_001, is_equal_to_string("PMGRID 512"));
  assert_that(eagle.config.Config_option_002, is_equal_to_string("ASMTH 1.25"));
  assert_that(eagle.config.Config_option_003, is_equal_to_string("RCUT 4.5"));
  assert_that(eagle.config.Config_option_004, is_equal_to_string("MULTIPLEDOMAINS 16"));
  assert_that(eagle.config.Config_option_005, is_equal_to_string("PEANOHILBERT "));
  assert_that(eagle.config.Config_option_006, is_equal_to_string("WALLCLOCK "));
  assert_that(eagle.config.Config_option_007, is_equal_to_string("MYSORT "));
  assert_that(eagle.config.Config_option_008, is_equal_to_string("DOUBLEPRECISION "));
  assert_that(eagle.config.Config_option_009, is_equal_to_string("SUBFIND "));
  assert_that(eagle.config.Config_option_010, is_equal_to_string("DENSITY_SPLIT_BY_TYPE 1+2+16+32"));
  assert_that(eagle.config.Config_option_011, is_equal_to_string("NO_ISEND_IRECV_IN_DOMAIN "));
  assert_that(eagle.config.Config_option_012, is_equal_to_string("FIX_PATHSCALE_MPI_STATUS_IGNORE_BUG "));
  assert_that(eagle.config.Config_option_013, is_equal_to_string("NOSTOP_WHEN_BELOW_MINTIMESTEP "));
  assert_that(eagle.config.Config_option_014, is_equal_to_string("OVERRIDE_STOP_FOR_SUBOPTIMUM_DOMAINS "));
  assert_that(eagle.config.Config_option_015, is_equal_to_string("LONGIDS "));
  assert_that(eagle.config.Config_option_016, is_equal_to_string("GENERATE_GAS_IN_ICS "));
  assert_that(eagle.config.Config_option_017, is_equal_to_string("HAVE_HDF5 "));
  assert_that(eagle.config.Config_option_018, is_equal_to_string("EAGLE "));
  assert_that(eagle.config.Config_option_019, is_equal_to_string("EAGLE_COOLING "));
  assert_that(eagle.config.Config_option_020, is_equal_to_string("EAGLE_SFR "));
  assert_that(eagle.config.Config_option_021, is_equal_to_string("EAGLE_STELLAR_FEEDBACK "));
  assert_that(eagle.config.Config_option_022, is_equal_to_string("EAGLE_STELLAR_FEEDBACK_METALS "));
  assert_that(eagle.config.Config_option_023, is_equal_to_string("EAGLE_TIMESTEP "));
  assert_that(eagle.config.Config_option_024, is_equal_to_string("EAGLE_TIMESTEP_LIMITER "));
  assert_that(eagle.config.Config_option_025, is_equal_to_string("EAGLE_BH_TIMESTEP "));
  assert_that(eagle.config.Config_option_026, is_equal_to_string("EAGLE_SFR_METALLICITY_DEPENDENT_SF_THRESHOLD "));
  assert_that(eagle.config.Config_option_027, is_equal_to_string("EAGLE_METALSMOOTHING "));
  assert_that(eagle.config.Config_option_028, is_equal_to_string("EAGLE_SNIA_IRON "));
  assert_that(eagle.config.Config_option_029, is_equal_to_string("EAGLE_TRACK_SNIA_MASS "));
  assert_that(eagle.config.Config_option_030, is_equal_to_string("EAGLE_TRACK_SNII_MASS "));
  assert_that(eagle.config.Config_option_031, is_equal_to_string("EAGLE_TRACK_AGB_MASS "));
  assert_that(eagle.config.Config_option_032, is_equal_to_string("EAGLE_SAMPLE_STELLAREVOLUTION "));
  assert_that(eagle.config.Config_option_033, is_equal_to_string("EAGLE_BH "));
  assert_that(eagle.config.Config_option_034, is_equal_to_string("EAGLE_BH_ACCRETION "));
  assert_that(eagle.config.Config_option_035, is_equal_to_string("EAGLE_BH_THERMALFEEDBACK "));
  assert_that(eagle.config.Config_option_036, is_equal_to_string("EAGLE_BH_OWLS_MERGERS "));
  assert_that(eagle.config.Config_option_037, is_equal_to_string("EAGLE_BH_MAX_MERGING_DISTANCE "));
  assert_that(eagle.config.Config_option_038, is_equal_to_string("EAGLE_BH_MAX_REPOSITION_DISTANCE "));
  assert_that(eagle.config.Config_option_039, is_equal_to_string("BH_ANG_MOM_ACCRETION "));
  assert_that(eagle.config.Config_option_040, is_equal_to_string("RGB_EAGLE_FEEDBACK "));
  assert_that(eagle.config.Config_option_041, is_equal_to_string("EAGLE_Z_DEP_FEEDBACK "));
  assert_that(eagle.config.Config_option_042, is_equal_to_string("EAGLE_DETACH_BH_DENSITY "));
  assert_that(eagle.config.Config_option_043, is_equal_to_string("EAGLE_PE_AGN_FIX_MS "));
  assert_that(eagle.config.Config_option_044, is_equal_to_string("FOF "));
  assert_that(eagle.config.Config_option_045, is_equal_to_string("FOF_PRIMARY_LINK_TYPES 2"));
  assert_that(eagle.config.Config_option_046, is_equal_to_string("FOF_SECONDARY_LINK_TYPES 1+16+32"));
  assert_that(eagle.config.Config_option_047, is_equal_to_string("EAGLE_ASSIGN_HOSTHALO_MASS "));
  assert_that(eagle.config.Config_option_048, is_equal_to_string("EAGLE_IO "));
  assert_that(eagle.config.Config_option_049, is_equal_to_string("EAGLE_OWLS_SNAPSHOT "));
  assert_that(eagle.config.Config_option_050, is_equal_to_string("EAGLE_HDF5_COMPRESSED_SNAPSHOT "));
  assert_that(eagle.config.Config_option_051, is_equal_to_string("EAGLE_EXTRA_ARRAYS "));
  assert_that(eagle.config.Config_option_052, is_equal_to_string("EAGLE_SNIPSHOTS "));
  assert_that(eagle.config.Config_option_053, is_equal_to_string("EAGLE_SORT_OUTPUT "));
  assert_that(eagle.config.Config_option_054, is_equal_to_string("EAGLE_SUPPRESS_MEMORY_TABLE_DUMP "));
  assert_that(eagle.config.Config_option_055, is_equal_to_string("EAGLE_OUTPUT_GRID "));
  assert_that(eagle.config.Config_option_056, is_equal_to_string("EAGLE_OUTPUT_LOS "));
  assert_that(eagle.config.Config_option_057, is_equal_to_string("ANARCHY_SPH "));
  assert_that(eagle.config.Config_option_058, is_equal_to_string("ANARCHY_SPH_PRESSURE_ENTROPY "));
  assert_that(eagle.config.Config_option_059, is_equal_to_string("SPH_KERNEL_C2 "));
  assert_that(eagle.config.SVN_Version, is_equal_to_string("26063"));
}
