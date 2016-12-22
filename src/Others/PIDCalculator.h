/*
 * PWMCalculator.h
 *
 *  Created on: 2016-12-22
 *      Author: Etienne
 */

#ifndef SRC_OTHERS_PIDCALCULATOR_H_
#define SRC_OTHERS_PIDCALCULATOR_H_


#include <atomic>
#include <memory>
#include <queue>
#include <string>

#include "Base.h"
#include "Controller.h"
#include "HAL/cpp/priority_mutex.h"
#include "LiveWindow/LiveWindow.h"
#include "Notifier.h"
#include "PIDInterface.h"
#include "PIDSource.h"
#include "Timer.h"

namespace frc {


/**
 * Class implements a PID Control Loop.
 *
 * Creates a separate thread which reads the given PIDSource and takes
 * care of the integral calculations, as well as writing the given PIDOutput.
 *
 * This feedback controller runs in discrete time, so time deltas are not used
 * in the integral and derivative calculations. Therefore, the sample rate
 * affects the controller's behavior for a given set of PID constants.
 */
class PIDCalculator : public LiveWindowSendable,
                      public PIDInterface,
                      public ITableListener {
 public:
	PIDCalculator(double p, double i, double d, double f = 0.0, double period = 0.05);
  virtual ~PIDCalculator();

  PIDCalculator(const PIDCalculator&) = delete;
  PIDCalculator& operator=(const PIDCalculator) = delete;

  virtual double Get() const;
  virtual void SetContinuous(bool continuous = true);
  virtual void SetInputRange(double minimumInput, double maximumInput);
  virtual void SetOutputRange(double minimumOutput, double maximumOutput);
  void SetPID(double p, double i, double d) override;
  virtual void SetPID(double p, double i, double d, double f);
  double GetP() const override;
  double GetI() const override;
  double GetD() const override;
  virtual double GetF() const;

  void SetInput(double input);
  double GetInput() const;

  void SetSetpoint(float setpoint) override;
  double GetSetpoint() const override;
  double GetDeltaSetpoint() const;

  double GetResult() const;

  virtual double GetError() const;
  virtual double GetAvgError() const;

  virtual void SetPIDSourceType(PIDSourceType pidSource);
  virtual PIDSourceType GetPIDSourceType() const;

  virtual void SetTolerance(double percent);
  virtual void SetAbsoluteTolerance(double absValue);
  virtual void SetPercentTolerance(double percentValue);
  virtual void SetToleranceBuffer(int buf = 1);
  virtual bool OnTarget() const;

  void Enable() override;
  void Disable() override;
  bool IsEnabled() const override;

  void Reset() override;

  void InitTable(std::shared_ptr<ITable> subtable) override;

 protected:


  std::shared_ptr<ITable> m_table;
  virtual void Calculate();
  virtual double CalculateFeedForward();
  double GetContinuousError(double error) const;

 private:
  // factor for "proportional" control
  double m_P;
  // factor for "integral" control
  double m_I;
  // factor for "derivative" control
  double m_D;
  // factor for "feed forward" control
  double m_F;
  // |maximum output|
  double m_maximumOutput = 1.0;
  // |minimum output|
  double m_minimumOutput = -1.0;
  // maximum input - limit setpoint to this
  double m_maximumInput = 0;
  // minimum input - limit setpoint to this
  double m_minimumInput = 0;
  // do the endpoints wrap around? eg. Absolute encoder
  bool m_continuous = false;
  // is the pid controller enabled
  bool m_enabled = false;
  // the prior error (used to compute velocity)
  double m_prevError = 0;
  // the sum of the errors for use in the integral calc
  double m_totalError = 0;
  enum {
    kAbsoluteTolerance,
    kPercentTolerance,
    kNoTolerance
  } m_toleranceType = kNoTolerance;

  // the percetage or absolute error that is considered on target.
  double m_tolerance = 0.05;
  double m_input = 0.0;
  double m_setpoint = 0;
  double m_prevSetpoint = 0;
  double m_error = 0;
  double m_result = 0;
  double m_period;

  PIDSourceType m_sourceType = PIDSourceType::kDisplacement;

  // Length of buffer for averaging for tolerances.
  std::atomic<unsigned> m_bufLength{1};
  std::queue<double> m_buf;
  double m_bufTotal = 0;

  mutable priority_recursive_mutex m_mutex;

  //std::unique_ptr<Notifier> m_controlLoop;
  Timer m_setpointTimer;

  std::shared_ptr<ITable> GetTable() const override;
  std::string GetSmartDashboardType() const override;
  void ValueChanged(ITable* source, llvm::StringRef key,
                    std::shared_ptr<nt::Value> value, bool isNew) override;
  void UpdateTable() override;
  void StartLiveWindowMode() override;
  void StopLiveWindowMode() override;
};

}  // namespace frc


#endif /* SRC_OTHERS_PIDCALCULATOR_H_ */
