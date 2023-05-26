using System.Security.Claims;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;

namespace WebApplication7.Controllers
{
    public class AccountController : Controller
    {
        private readonly string _connectionString = "server=127.0.0.1;uid=andrew;password=#Pa55w0rd;database=webcsharp";

        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(string email, string password)
        {
            try
            {
                await using (var conn = new MySqlConnection(_connectionString))
                {
                    await conn.OpenAsync();

                    await using (var command = conn.CreateCommand())
                    {
                        command.CommandText = "SELECT COUNT(*) FROM User WHERE name = @name AND password = @password";
                        command.Parameters.AddWithValue("@name", email);
                        command.Parameters.AddWithValue("@password", password);

                        var result = await command.ExecuteScalarAsync();

                        if (result != null && Convert.ToInt32(result) > 0)
                        {
                            var claims = new List<Claim>
                            {
                                new Claim(ClaimTypes.Name, email)
                                // Add any additional claims as needed
                            };

                            var claimsIdentity = new ClaimsIdentity(
                                claims, CookieAuthenticationDefaults.AuthenticationScheme);

                            await HttpContext.SignInAsync(
                                CookieAuthenticationDefaults.AuthenticationScheme,
                                new ClaimsPrincipal(claimsIdentity));
                            
                            Console.WriteLine("Successful login");
                            return RedirectToAction("Index", "Home");
                        }
                        else
                        {
                            // Invalid credentials, return an error or redirect to the login page with a message
                            ViewBag.ErrorMessage = "Invalid email or password.";
                            Console.WriteLine("Nono login");

                            return View();
                        }
                    }
                }
            }
            catch (MySqlException ex)
            {
                Console.WriteLine(ex.Message);
                // Handle the exception, return an error or redirect to the login page with a message
                ViewBag.ErrorMessage = "An error occurred during login.";
                return View();
            }
        }
    }
}
