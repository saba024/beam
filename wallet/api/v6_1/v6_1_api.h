// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "wallet/api/v6_0/v6_api.h"
#include "v6_1_api_defs.h"

namespace beam::wallet
{
    class V61Api
        : public V6Api
        , public IWalletObserver
    {
    public:
        // CTOR MUST BE SAFE TO CALL FROM ANY THREAD
        V61Api(IWalletApiHandler& handler, unsigned long avMajor, unsigned long avMinor, const ApiInitData& init);
        ~V61Api() override;

        V6_1_API_METHODS(BEAM_API_PARSE_FUNC)
        V6_1_API_METHODS(BEAM_API_RESPONSE_FUNC)
        V6_1_API_METHODS(BEAM_API_HANDLE_FUNC)

    protected:
        void onSyncProgress(int done, int total) override;

    private:
        bool _evSubscribed = false;
        std::string _apiVersion;
        unsigned _apiVersionMajor;
        unsigned _apiVersionMinor;
        Wallet::Ptr _wallet;
    };
}
