#include "contact_details.hh"

#include <string>

ContactDetails::ContactDetails(const std::string& telephone_number,
                               const std::string& personal_email)
    : number_(telephone_number)
    , email_(personal_email)
{}

bool is_digit(const std::string& s)
{
    if (s.size() == 0)
        return false;
    for (const char c : s)
    {
        int v = c;
        if (!(v >= 48 && v <= 57))
            return false;
    }
    return true;
}

std::optional<ContactDetails>
ContactDetails::makeDetails(const std::string& telephone_number,
                            const std::string& personal_email)
{
    if (telephone_number != "" && personal_email != ""
        && personal_email.find('@', 0) != std::string::npos
        && is_digit(telephone_number))
        return ContactDetails(telephone_number, personal_email);
    return std::nullopt;
}

std::ostream& operator<<(std::ostream& os,
                         const ContactDetails& contact_details)
{
    return os << contact_details.number_ << ", " << contact_details.email_
              << '\n';
}
