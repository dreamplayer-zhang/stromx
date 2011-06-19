#include "TimePeriod.h"

#include "Config.h"

#include <stream/DataContainer.h>
#include <stream/DataProvider.h>
#include <stream/Id2DataPair.h>
#include <stream/OperatorException.h>

#include <boost/thread/mutex.hpp>

using namespace stream;

namespace base
{
    const std::string TimePeriod::NAME("Time period");
    
    const std::string TimePeriod::PACKAGE(PACKAGE_NAME);
    const Version TimePeriod::VERSION(BASE_VERSION_MAJOR, BASE_VERSION_MINOR);
    
    TimePeriod::TimePeriod()
      : Operator(NAME, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters()),
        m_isFirstRun(true)
    {
    }
    
    void TimePeriod::activate()
    {
        m_isFirstRun = true;
    }


    void TimePeriod::setParameter(unsigned int id, const Data& value)
    {
        try
        {
            switch(id)
            {
            case PERIOD:
            {
                m_period = dynamic_cast<const UInt32 &>(value);
                break;
            }
            default:
                throw ParameterIdException(id, *this);
            }
        }
        catch(std::bad_cast&)
        {
            throw ParameterTypeException(*parameters()[id], *this);
        }
    }

    const Data& TimePeriod::getParameter(unsigned int id)
    {
        switch(id)
        {
        case PERIOD:
            return m_period;
        default:
            throw ParameterIdException(id, *this);
        }
    }  
    
    void TimePeriod::execute(DataProvider& provider)
    {
        Id2DataPair inputDataMapper(INPUT);
        provider.receiveInputData(inputDataMapper);
        
        try
        {
            if(m_isFirstRun)
            {
                boost::this_thread::sleep(boost::posix_time::millisec(m_period));
                m_isFirstRun = false;
            }
            else
            {
                boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
                boost::posix_time::time_duration passedTime = now - m_lastExecute;
                
                if(passedTime.total_milliseconds() < m_period)
                {
                    UInt32 remainingMilliseconds(m_period - passedTime.total_milliseconds());
                    boost::this_thread::sleep(boost::posix_time::millisec(remainingMilliseconds));
                }
            }
        }
        catch(boost::thread_interrupted&)
        {
            throw InterruptException();
        }
        
        m_lastExecute = boost::posix_time::second_clock::local_time();
        
        Id2DataPair outputDataMapper(OUTPUT, inputDataMapper.data());
        provider.sendOutputData( outputDataMapper);
    }
    
    const std::vector< Description* > TimePeriod::setupInputs()
    {
        std::vector<Description*> inputs;
        
        Description* input = new Description(OUTPUT, DataType::DATA);
        input->setName("Input");
        inputs.push_back(input);
        
        return inputs;
    }
    
    const std::vector< stream::Description* > TimePeriod::setupOutputs()
    {
        std::vector<Description*> outputs;
        
        Description* output = new Description(OUTPUT, DataType::DATA);
        output->setName("Output");
        outputs.push_back(output);
        
        return outputs;
    }
    
    const std::vector< stream::Parameter* > TimePeriod::setupParameters()
    {
        std::vector<stream::Parameter*> parameters;
        
        Parameter* period = new Parameter(PERIOD, DataType::UINT_32);
        period->setName("Period (milliseconds)");
        period->setActiveAccessMode(Parameter::WRITE);
        period->setInactiveAccessMode(Parameter::WRITE);
        parameters.push_back(period);
                                    
        return parameters;
    }
} 
