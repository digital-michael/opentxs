/************************************************************
 *
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  EMAIL:
 *  fellowtraveler@opentransactions.org
 *
 *  WEBSITE:
 *  http://www.opentransactions.org/
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This Source Code Form is subject to the terms of the
 *   Mozilla Public License, v. 2.0. If a copy of the MPL
 *   was not distributed with this file, You can obtain one
 *   at http://mozilla.org/MPL/2.0/.
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will
 *   be useful, but WITHOUT ANY WARRANTY; without even the
 *   implied warranty of MERCHANTABILITY or FITNESS FOR A
 *   PARTICULAR PURPOSE.  See the Mozilla Public License
 *   for more details.
 *
 ************************************************************/

#include "opentxs/core/app/Api.hpp"

#include "opentxs/client/OT_API.hpp"
#include "opentxs/client/OT_ME.hpp"
#include "opentxs/client/OTAPI_Exec.hpp"
#include "opentxs/core/app/Settings.hpp"
#include "opentxs/core/crypto/OTCachedKey.hpp"
#include "opentxs/core/Log.hpp"

#include <assert.h>

namespace opentxs
{

Api::Api(Settings& config)
{
    Init(config);
}

void Api::Init(Settings& config)
{
    if (!Log::Init("client")) {
        assert(false);
    }

    // Changed this to otErr (stderr) so it doesn't muddy the output.
    otLog3 << "\n\nWelcome to Open Transactions -- version "
           << Log::Version() << "\n";

    otLog4 << "(transport build: OTMessage -> OTEnvelope -> ZMQ )\n";

// SIGNALS
#if defined(OT_SIGNAL_HANDLING)
    Log::SetupSignalHandler();
// This is optional! You can always remove it using the OT_NO_SIGNAL_HANDLING
// option, and plus, the internals only execute once anyway. (It keeps count.)
#endif

    // TODO in the case of Windows, figure err into this return val somehow.
    // (Or log it or something.)

    ot_api_.reset(new OT_API(config, lock_));
    otapi_exec_.reset(new OTAPI_Exec(*ot_api_, lock_));
    ot_me_.reset(new OT_ME(lock_));
}

OTAPI_Exec& Api::Exec()
{
    OT_ASSERT(otapi_exec_);

    return *otapi_exec_;
}

OT_API& Api::OTAPI()
{
    OT_ASSERT(ot_api_);

    return *ot_api_;
}

OT_ME& Api::OTME(const std::string&)
{
    OT_ASSERT(ot_me_);

    return *ot_me_;
}

void Api::Cleanup()
{
    OTCachedKey::Cleanup();
}

Api::~Api() {
    Cleanup();
    ot_me_.reset();
    otapi_exec_.reset();
    ot_api_.reset();
}
}  // namespace opentxs
