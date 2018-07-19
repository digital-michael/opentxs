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

#ifndef IMPLEMENTATION_OPENTXS_CRYPTO_KEY_ELLIPTICCURVE_HPP
#define IMPLEMENTATION_OPENTXS_CRYPTO_KEY_ELLIPTICCURVE_HPP

#include "Internal.hpp"

#include "Asymmetric.hpp"

namespace opentxs::crypto::key::implementation
{
class EllipticCurve : virtual public key::EllipticCurve, public Asymmetric
{
    using ot_super = Asymmetric;

public:
    bool IsEmpty() const override;
    virtual bool GetKey(Data& key) const override;
    virtual bool GetKey(proto::Ciphertext& key) const override;
    bool GetPublicKey(String& strKey) const override;
    virtual bool GetPublicKey(Data& key) const override;
    using ot_super::Path;
    const std::string Path() const override;
    bool Path(proto::HDPath& output) const override;
    virtual bool ReEncryptPrivateKey(
        const OTPassword& theExportPassword,
        bool bImporting) const override;
    std::shared_ptr<proto::AsymmetricKey> Serialize() const override;
    bool TransportKey(Data& publicKey, OTPassword& privateKey) const override;

    virtual bool SetKey(const Data& key) override;
    virtual bool SetKey(std::unique_ptr<proto::Ciphertext>& key) override;

    virtual ~EllipticCurve() = default;

protected:
    OTData key_;
    std::unique_ptr<proto::Ciphertext> encrypted_key_{nullptr};
    std::shared_ptr<proto::HDPath> path_{nullptr};
    std::unique_ptr<proto::Ciphertext> chain_code_{nullptr};

    explicit EllipticCurve(
        const proto::AsymmetricKeyType keyType,
        const proto::KeyRole role);
    explicit EllipticCurve(const proto::AsymmetricKey& serializedKey);
    explicit EllipticCurve(
        const proto::AsymmetricKeyType keyType,
        const String& publicKey);

private:
    friend class crypto::EcdsaProvider;

    EllipticCurve* clone() const override final;

    EllipticCurve() = delete;
    EllipticCurve(const EllipticCurve&) = delete;
    EllipticCurve(EllipticCurve&&) = delete;
    EllipticCurve& operator=(const EllipticCurve&) = delete;
    EllipticCurve& operator=(EllipticCurve&&) = delete;
};
}  // namespace opentxs::crypto::key::implementation
#endif  // IMPLEMENTATION_OPENTXS_CRYPTO_KEY_ELLIPTICCURVE_HPP