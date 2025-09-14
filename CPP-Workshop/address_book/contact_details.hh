#pragma once

#include <iostream>
#include <optional>
#include <string>
class ContactDetails
{
private:
    ContactDetails(const std::string& telephone_number,
                   const std::string& personal_email);
    std::string number_;
    std::string email_;

public:
    static std::optional<ContactDetails>
    makeDetails(const std::string& telephone_number,
                const std::string& personal_email);
    friend std::ostream& operator<<(std::ostream& os,
                                    const ContactDetails& contact_details);
};
std::ostream& operator<<(std::ostream& os,
                         const ContactDetails& contact_details);
