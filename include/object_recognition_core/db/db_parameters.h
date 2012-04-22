/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef DB_PARAMETERS_H_
#define DB_PARAMETERS_H_

namespace object_recognition_core
{
  namespace db
  {
    /** A class that stores the common parameters for the object DB
     * If it is not from a type provided by object_recognition_core, it is of type NONCORE
     */
    class ObjectDbParameters
    {
    public:
      enum ObjectDbType
      {
        EMPTY, COUCHDB, FILESYSTEM, NONCORE
      };
      ObjectDbParameters();

      /** Default constructor for certain types
       * @param type Default type
       */
      explicit
      ObjectDbParameters(const std::string& type);

      /** Default constructor for certain types
       * @param type Default type
       */
      explicit
      ObjectDbParameters(ObjectDbType type);

      /**
       * @param params A map between some db parameters and their value
       */
      explicit
      ObjectDbParameters(const or_json::mObject& params);

      static ObjectDbType
      StringToType(const std::string & type);

      static std::string
      TypeToString(const ObjectDbParameters::ObjectDbType & type);

      ObjectDbType
      type() const
      {
        return type_;
      }

      template<typename T>
      void
      set_parameter(const std::string & key, const T & value)
      {
        raw_[key] = or_json::mValue(value);
        if (key == "type")
          type_ = StringToType(value);
      }

      or_json::mValue
      at(const std::string & key) const
      {
        return raw_.at(key);
      }

      or_json::mObject
      raw() const
      {
        return raw_;
      }
    protected:
      /** The type of the collection 'CouchDB' ... */
      ObjectDbType type_;
      /** All the raw parameters: they are of integral types */
      or_json::mObject raw_;
      void
      FillParameters(const or_json::mObject& json_params);
    };
  }
}

#endif /* DB_PARAMETERS_H_ */
