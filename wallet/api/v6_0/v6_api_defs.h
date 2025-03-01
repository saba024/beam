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

#include <boost/optional.hpp>
#include "wallet/core/wallet.h"
#include "wallet/api/base/api_base.h"
#include "wallet/api/base/api_errors_imp.h"
#include "wallet/client/extensions/offers_board/swap_offer.h"
#include "bvm/invoke_data.h"

namespace beam::wallet
{
#if defined(BEAM_ATOMIC_SWAP_SUPPORT)
#define V6_SWAP_METHODS(macro) \
    macro(OffersList,         "swap_offers_list",          API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(OffersBoard,        "swap_offers_board",         API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(CreateOffer,        "swap_create_offer",         API_WRITE_ACCESS, API_SYNC, APPS_BLOCKED)  \
    macro(PublishOffer,       "swap_publish_offer",        API_WRITE_ACCESS, API_SYNC, APPS_BLOCKED)  \
    macro(AcceptOffer,        "swap_accept_offer",         API_WRITE_ACCESS, API_SYNC, APPS_BLOCKED)  \
    macro(OfferStatus,        "swap_offer_status",         API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(DecodeToken,        "swap_decode_token",         API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(GetBalance,         "swap_get_balance",          API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(RecommendedFeeRate, "swap_recommended_fee_rate", API_READ_ACCESS,  API_SYNC, APPS_BLOCKED)  \
    macro(CancelOffer,        "swap_cancel_offer",         API_WRITE_ACCESS, API_SYNC, APPS_BLOCKED)
#else  // !BEAM_ATOMIC_SWAP_SUPPORT
#define V6_SWAP_METHODS(macro)
#endif  // BEAM_ATOMIC_SWAP_SUPPORT

#define V6_API_METHODS(macro) \
    macro(CreateAddress,         "create_address",          API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(DeleteAddress,         "delete_address",          API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(EditAddress,           "edit_address",            API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(AddrList,              "addr_list",               API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(ValidateAddress,       "validate_address",        API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(Send,                  "tx_send",                 API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(Issue,                 "tx_asset_issue",          API_WRITE_ACCESS, API_SYNC,  APPS_BLOCKED)   \
    macro(Consume,               "tx_asset_consume",        API_WRITE_ACCESS, API_SYNC,  APPS_BLOCKED)   \
    macro(TxAssetInfo,           "tx_asset_info",           API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(Status,                "tx_status",               API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(Split,                 "tx_split",                API_WRITE_ACCESS, API_SYNC,  APPS_BLOCKED)   \
    macro(TxCancel,              "tx_cancel",               API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(TxDelete,              "tx_delete",               API_WRITE_ACCESS, API_SYNC,  APPS_ALLOWED)   \
    macro(GetUtxo,               "get_utxo",                API_READ_ACCESS,  API_SYNC,  APPS_BLOCKED)   \
    macro(TxList,                "tx_list",                 API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(WalletStatusApi,       "wallet_status",           API_READ_ACCESS,  API_SYNC,  APPS_BLOCKED)   \
    macro(GenerateTxId,          "generate_tx_id",          API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(ExportPaymentProof,    "export_payment_proof",    API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(VerifyPaymentProof,    "verify_payment_proof",    API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(GetAssetInfo,          "get_asset_info",          API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(SetConfirmationsCount, "set_confirmations_count", API_WRITE_ACCESS, API_SYNC,  APPS_BLOCKED)   \
    macro(GetConfirmationsCount, "get_confirmations_count", API_READ_ACCESS,  API_SYNC,  APPS_ALLOWED)   \
    macro(InvokeContract,        "invoke_contract",         API_WRITE_ACCESS, API_ASYNC, APPS_ALLOWED)   \
    macro(ProcessInvokeData,     "process_invoke_data",     API_WRITE_ACCESS, API_ASYNC, APPS_ALLOWED)   \
    macro(BlockDetails,          "block_details",           API_READ_ACCESS,  API_ASYNC, APPS_ALLOWED)   \
    macro(CalcChange,            "calc_change",             API_READ_ACCESS,  API_SYNC, APPS_ALLOWED)    \
    macro(ChangePassword,        "change_password",         API_WRITE_ACCESS, API_SYNC, APPS_BLOCKED)    \
    V6_SWAP_METHODS(macro)

    struct CalcChange
    {
        Amount amount;
        Amount explicitFee = 0;
        boost::optional<Asset::ID> assetId;
        bool isPushTransaction = false;

        struct Response
        {
            Amount change;
            Amount assetChange;
            Amount explicitFee;
        };
    };

    struct ChangePassword
    {
        std::string newPassword;
        struct Response
        {
        };
    };

    struct AddressData
    {
        boost::optional<std::string> comment;
        boost::optional<beam::wallet::WalletAddress::ExpirationStatus> expiration;
    };

    struct CreateAddress : AddressData
    {
        TokenType type = TokenType::RegularOldStyle;
        uint32_t offlinePayments = 1;

        struct Response
        {
            std::string token;
        };
    };

    struct DeleteAddress
    {
        std::string token;
        struct Response {};
    };

    struct EditAddress : AddressData
    {
        std::string token;
        struct Response {};
    };

    struct AddrList
    {
        bool own = false;

        struct Response
        {
            std::vector<WalletAddress> list;
        };
    };

    struct ValidateAddress
    {
        std::string token;

        struct Response
        {
            bool isValid;
            bool isMine;
            TokenType type = TokenType::Unknown;
            boost::optional<size_t> payments;
        };
    };

    struct Send
    {
        Amount value = 0;
        Amount fee = 0;

        std::string tokenTo;
        std::string comment;

        TxParameters txParameters;
        TxAddressType addressType = TxAddressType::Unknown;

        boost::optional<std::string> tokenFrom;
        boost::optional<CoinIDList>  coins;
        boost::optional<TxID>        txId;
        boost::optional<Asset::ID>   assetId;

        struct Response
        {
            TxID txId;
        };
    };

    struct Issue
    {
        Amount value = 0;
        Amount fee = 0;
        Asset::ID assetId;
        boost::optional<CoinIDList> coins;
        boost::optional<TxID> txId;

        struct Response
        {
            TxID txId;
        };
    };

    struct Consume
    {
        Amount value = 0;
        Amount fee = 0;
        Asset::ID assetId;
        boost::optional<CoinIDList> coins;
        boost::optional<TxID> txId;

        struct Response
        {
            TxID txId;
        };
    };

    struct TxAssetInfo
    {
        Asset::ID assetId;
        boost::optional<TxID> txId;

        struct Response
        {
            TxID txId;
        };
    };

    struct Status
    {
        TxID txId;

        struct Response
        {
            TxDescription tx;
            Height txHeight;
            Height systemHeight;
            uint64_t confirmations;
        };
    };

    struct Split
    {
        Amount fee = 0;
        AmountList coins;
        boost::optional<TxID> txId;
        boost::optional<Asset::ID> assetId;

        struct Response
        {
            TxID txId;
        };
    };

    struct TxCancel
    {
        TxID txId;

        struct Response
        {
            bool result;
        };
    };


    struct TxDelete
    {
        TxID txId;

        struct Response
        {
            bool result;
        };
    };

#define BEAM_GET_UTXO_RESPONSE_FIELDS(macro) \
    macro(id,              std::string) \
    macro(asset_id,        Asset::ID) \
    macro(amount,          Amount) \
    macro(type,            std::string) \
    macro(maturity,        Height) \
    macro(createTxId,      std::string) \
    macro(spentTxId,       std::string) \
    macro(status,          uint32_t) \
    macro(status_string,   std::string)

    struct GetUtxo
    {
        uint32_t count = 0;
        uint32_t skip = 0;
        bool withAssets = false;

        struct
        {
            boost::optional<Asset::ID> assetId;
        } filter;

        struct
        {
            std::string field = "default";
            bool desc = false;
        } sort;

        struct Response
        {
            struct Coin
            {
                #define MACRO(name, type) type name = {};
                BEAM_GET_UTXO_RESPONSE_FIELDS(MACRO)
                #undef MACRO
            };
            std::vector<Coin> coins;
            uint32_t confirmations_count = 0;

            template<typename T>
            void EmplaceCoin(const T& c)
            {
                auto& t = coins.emplace_back();
                t.id = c.toStringID();
                t.asset_id = c.getAssetID();
                t.amount = c.getAmount();
                t.type = c.getType();
                t.maturity = c.get_Maturity(confirmations_count);
                t.createTxId = GetCoinCreateTxID(c);
                t.spentTxId = GetCoinSpentTxID(c);
                t.status = GetCoinStatus(c);
                t.status_string = c.getStatusString();
            };
        };
    };

    struct TxList
    {
        bool withAssets = false;

        struct
        {
            boost::optional<TxStatus>  status;
            boost::optional<Height>    height;
            boost::optional<Asset::ID> assetId;
        } filter;

        uint32_t count = 0;
        uint32_t skip = 0;

        struct Response
        {
            std::vector<Status::Response> resultList;
        };
    };

    struct WalletStatusApi
    {
        bool withAssets = false;
        struct Response
        {
            beam::Height currentHeight = 0;
            Merkle::Hash currentStateHash;
            Merkle::Hash prevStateHash;
            double difficulty = 0;
            Amount available = 0;
            Amount receiving = 0;
            Amount sending = 0;
            Amount maturing = 0;
            boost::optional<storage::Totals> totals;
        };
    };

    struct GenerateTxId
    {
        struct Response
        {
            TxID txId;
        };
    };

    struct ExportPaymentProof
    {
        TxID txId;

        struct Response
        {
            ByteBuffer paymentProof;
        };
    };

    struct VerifyPaymentProof
    {
        ByteBuffer paymentProof;
        struct Response
        {
            boost::optional<storage::PaymentInfo> paymentInfo;
            boost::optional<storage::ShieldedPaymentInfo> shieldedPaymentInfo;
        };
    };

    struct GetAssetInfo
    {
        Asset::ID assetId;
        struct Response
        {
            Response() = default;
            WalletAsset AssetInfo;
        };
    };

    struct SetConfirmationsCount
    {
        uint32_t count = 0;
        struct Response {
            uint32_t count;
        };
    };

    struct GetConfirmationsCount
    {
        struct Response
        {
            uint32_t count;
        };
    };

    struct InvokeContract
    {
        std::vector<uint8_t> contract;
        std::string args;
        bool createTx = true;

        struct Response
        {
            boost::optional<std::string> output;
            boost::optional<beam::ByteBuffer> invokeData;
            boost::optional<TxID> txid = TxID();
        };
    };

    struct ProcessInvokeData
    {
        beam::ByteBuffer invokeData;
        struct Response
        {
            TxID txid = TxID();
        };
    };

    struct BlockDetails
    {
        Height blockHeight;

        struct Response
        {
            Height height;
            std::string blockHash;
            std::string previousBlock;
            std::string chainwork;
            std::string kernels;
            std::string definition;
            Timestamp timestamp;
            std::string pow;
            double difficulty;
            uint32_t packedDifficulty;
            std::string rulesHash;
        };
    };

    #if defined(BEAM_ATOMIC_SWAP_SUPPORT)
    struct OfferInput
    {
        Amount beamAmount = 0;
        Amount swapAmount = 0;
        AtomicSwapCoin swapCoin = AtomicSwapCoin::Bitcoin;
        bool isBeamSide = true;
        Amount beamFee = 0;
        Amount swapFeeRate = 0;
        Height offerLifetime = 15;
        std::string comment;
    };

    struct OffersList
    {
        struct
        {
            boost::optional<AtomicSwapCoin> swapCoin;
            boost::optional<SwapOfferStatus> status;
        } filter;
        struct Response
        {
            std::vector<WalletAddress> addrList;
            Height systemHeight;
            std::vector<SwapOffer> list;
        };
    };

    struct OffersBoard
    {
        struct
        {
            boost::optional<AtomicSwapCoin> swapCoin;
        } filter;
        struct Response
        {
            std::vector<WalletAddress> addrList;
            Height systemHeight;
            std::vector<SwapOffer> list;
        };
    };

    struct CreateOffer : public OfferInput
    {
        CreateOffer() = default;
        explicit CreateOffer(const OfferInput& oi) : OfferInput(oi) {}
        struct Response
        {
            std::vector<WalletAddress> addrList;
            Height systemHeight;
            std::string token;
            TxID txId;
        };
    };

    struct PublishOffer
    {
        std::string token;
        struct Response
        {
            std::vector<WalletAddress> addrList;
            Height systemHeight;
            SwapOffer offer;
        };
    };

    struct AcceptOffer
    {
        std::string token;
        Amount beamFee = 0;
        Amount swapFeeRate = 0;
        std::string comment;
        struct Response
        {
            std::vector<WalletAddress> addrList;
            Height systemHeight;
            SwapOffer offer;
        };
    };

    struct OfferStatus
    {
        TxID txId;
        struct Response
        {
            Height systemHeight;
            SwapOffer offer;
        };
    };

    struct DecodeToken
    {
        std::string token;
        struct Response
        {
            SwapOffer offer;
            bool isMyOffer;
            bool isPublic;
        };
    };

    struct GetBalance
    {
        AtomicSwapCoin coin;
        struct Response
        {
            Amount available;
        };
    };

    struct RecommendedFeeRate
    {
        AtomicSwapCoin coin;
        struct Response
        {
            Amount feeRate;
        };
    };

    struct CancelOffer: public TxCancel
    {
        struct Response: public TxCancel::Response
        {
        };
    };
#endif  // BEAM_ATOMIC_SWAP_SUPPORT
}
