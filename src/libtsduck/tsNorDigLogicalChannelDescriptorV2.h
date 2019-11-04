//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2019, Thierry Lelegard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a NorDig logical_channel_descriptor (V2).
//!  This is a private descriptor, must be preceeded by the NorDig PDS.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"

namespace ts {
    //!
    //! Representation of a NorDig logical_channel_descriptor (V2).
    //!
    //! This is a private descriptor, must be preceeded by the NorDig PDS.
    //! @see NorDig Unified Requirements ver. 3.1.1, 12.2.9.3.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL NorDigLogicalChannelDescriptorV2 : public AbstractDescriptor
    {
    public:
        //!
        //! Service entry.
        //!
        struct TSDUCKDLL Service
        {
            // Public members
            uint16_t service_id;  //!< Service id.
            bool     visible;     //!< Service is visible.
            uint16_t lcn;         //!< Logical channel number, 10 bits.

            //!
            //! Constructor
            //! @param [in] id Service id.
            //! @param [in] visible Service is visible.
            //! @param [in] lcn Logical channel number.
            //!
            Service(uint16_t id = 0, bool visible = true, uint16_t lcn = 0);
        };

        //!
        //! List of service entries.
        //!
        typedef std::list<Service> ServiceList;

        //!
        //! Channel list entry.
        //!
        struct TSDUCKDLL ChannelList
        {
            // Public members
            uint8_t     channel_list_id;    //!< Channel list id.
            UString     channel_list_name;  //!< Channel list name.
            UString     country_code;       //!< 3-character country code.
            ServiceList services;           //!< List of services.

            //!
            //! Constructor
            //! @param [in] id Channel list id.
            //! @param [in] name Channel list name.
            //! @param [in] country Country code.
            //!
            ChannelList(uint8_t id = 0, const UString& name = UString(), const UString& country = UString());
        };

        //!
        //! List of channel list entries.
        //!
        typedef std::list<ChannelList> ChannelListList;

        // NorDigLogicalChannelDescriptorV2 public members:
        ChannelListList entries;  //!< List of channel list entries.

        //!
        //! Default constructor.
        //!
        NorDigLogicalChannelDescriptorV2();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        NorDigLogicalChannelDescriptorV2(DuckContext& duck, const Descriptor& bin);

        // Inherited methods
        virtual void serialize(DuckContext&, Descriptor&) const override;
        virtual void deserialize(DuckContext&, const Descriptor&) override;
        virtual void fromXML(DuckContext&, const xml::Element*) override;
        DeclareDisplayDescriptor();

    protected:
        // Inherited methods
        virtual void buildXML(DuckContext&, xml::Element*) const override;
    };
}