const login_email = document.getElementById('email');
const login_password = document.getElementById('password');
const login_button = document.getElementById('btn-submit');

const cek_reg_email = localStorage.getItem('register_email')
const cek_reg_password = localStorage.getItem('register_password')
const cek_log_email = localStorage.getItem('login_email')
const cek_log_password = localStorage.getItem('login_password')

if (cek_reg_email, cek_reg_password, cek_log_email, cek_log_password != null) {
    window.location = 'account.html'
}

login_email.value = localStorage.getItem('register_email')
login_password.value = localStorage.getItem('register_password')

login_button.addEventListener('click', function () {

    const valid_email = localStorage.getItem('register_email')
    const valid_password = localStorage.getItem('register_password')

    if (login_email.value, login_password.value === '') {
        alert('Dados inválidos ❌')
        return false
    }

    if (login_email.value != valid_email || login_password.value != valid_password) {
        alert('Sua conta não foi encontrada! Registrar agora!!')
        return false
    } else {
        localStorage.setItem('login_email', login_email.value)
        localStorage.setItem('login_password', login_password.value)
        alert('Login efetuado com sucesso ✅')
        window.location = 'account.html'
    }

})